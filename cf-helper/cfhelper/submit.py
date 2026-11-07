"""cf submit - open the Codeforces submit page with your code copied, then show the verdict.

Codeforces blocks scripted submissions (Cloudflare), so the submit itself happens in your
browser: the code is on the clipboard, you paste and click Submit. The verdict is then read
from the public API, which needs no login.
"""

import json
import re
import subprocess
import time
import urllib.error
import urllib.request
import webbrowser
from pathlib import Path

import click

from .config import load_config, set_config_value
from .utils import print_success, print_error, print_warning, print_info


def find_problem(problem, contest):
    """Return (contest_id, index, sol_path)."""
    cwd = Path.cwd()
    if problem:
        index = problem.upper()
        if contest:
            folder = Path(load_config()['base_dir']) / str(contest) / index
        else:
            folder, contest = cwd / index, cwd.name
        return str(contest), index, folder / 'sol.cpp'

    # No argument: we are inside the problem folder
    m = re.fullmatch(r'(\d+)([A-Za-z]\d?)', cwd.name)
    if m:  # e.g. Contests/2194B (single problem)
        return m.group(1), m.group(2).upper(), cwd / 'sol.cpp'
    return cwd.parent.name, cwd.name.upper(), cwd / 'sol.cpp'  # e.g. Contests/2278/A


def api_status(handle):
    url = f'https://codeforces.com/api/user.status?handle={handle}&count=10'
    try:
        with urllib.request.urlopen(url, timeout=15) as r:
            data = json.load(r)
    except urllib.error.URLError:
        # Some Python installs lack SSL certificates; curl uses the system ones
        out = subprocess.run(['curl', '-s', '-m', '15', url], capture_output=True, text=True).stdout
        data = json.loads(out)
    if data.get('status') != 'OK':
        raise click.ClickException(f"Codeforces API: {data.get('comment')}")
    return data['result']


@click.command()
@click.argument('problem', required=False)
@click.option('-c', '--contest', type=int, default=None, help='Contest ID (default: from the folder name)')
@click.option('--handle', default=None, help='Your Codeforces handle (saved after the first time)')
def main(problem, contest, handle):
    """Submit a solution: `cf submit A` in a contest folder, or `cf submit` in a problem folder."""
    contest_id, index, sol = find_problem(problem, contest)
    if not contest_id.isdigit():
        raise click.ClickException(f'Could not tell the contest ID from the folder name "{contest_id}". '
                                   'Use -c <contest-id>.')
    if not sol.exists():
        raise click.ClickException(f'Solution not found: {sol}')

    handle = handle or load_config().get('cf_handle')
    if not handle:
        handle = click.prompt('Your Codeforces handle').strip()
    set_config_value('cf_handle', handle)

    subprocess.run(['pbcopy'], input=sol.read_text(), text=True, check=True)
    url = f'https://codeforces.com/contest/{contest_id}/submit/{index}'
    started = int(time.time()) - 5
    webbrowser.open(url)

    print_success(f'Copied {sol.parent.name}/sol.cpp to the clipboard.')
    print_info(f'Opened {url}')
    print('Paste (Cmd+V) into the code box and click Submit. Waiting for your submission... (Ctrl+C to stop)')

    seen = None
    try:
        for _ in range(600):  # about 10 minutes
            time.sleep(2)
            try:
                subs = api_status(handle)
            except Exception:
                continue  # API hiccup or rate limit: try again
            mine = [s for s in subs if s['creationTimeSeconds'] >= started
                    and str(s['problem'].get('contestId')) == contest_id
                    and s['problem']['index'] == index]
            if not mine:
                continue
            s = mine[0]
            verdict = s.get('verdict')
            if verdict in (None, 'TESTING'):
                if seen is None:
                    print_info(f"Submission {s['id']} found, judging...")
                seen = s['id']
                continue

            tests = s.get('passedTestCount', 0)
            ms, kb = s.get('timeConsumedMillis', 0), s.get('memoryConsumedBytes', 0) // 1024
            print()
            if verdict == 'OK':
                print_success(f'Accepted ✓  ({tests} tests, {ms} ms, {kb} KB)')
            else:
                name = verdict.replace('_', ' ').title()
                print_error(f'{name} ✗  on test {tests + 1}  ({ms} ms, {kb} KB)')
            print(f"https://codeforces.com/contest/{contest_id}/submission/{s['id']}")
            return
        print_warning('No verdict after 10 minutes. Check the site.')
    except KeyboardInterrupt:
        print_warning('\nStopped waiting. Your submission (if sent) is still being judged on the site.')
