"""ac - AtCoder helper: login, fetch samples (contest or single problem), submit and show the verdict.

Problems live in <repo>/Atcoder/<contest>/<LETTER>/ with sol.cpp, in*.txt / out*.txt and .ac.json.
Test them with the normal `run` command.
"""

import html
import json
import re
import shutil
import subprocess
import time
import urllib.error
import urllib.parse
import urllib.request
import webbrowser
from pathlib import Path

import click

from .config import load_config
from .sites import AtCoder, config_for
from .utils import print_success, print_error, print_warning, print_info, request_cd, open_in_editor

BASE = 'https://atcoder.jp'
AUTH_FILE = Path.home() / '.cfhelper' / 'atcoder.json'


# ---------- HTTP ----------

def load_cookie():
    if AUTH_FILE.exists():
        return json.loads(AUTH_FILE.read_text()).get('session')
    return None


def fetch(url, cookie=None, data=None):
    """Return (final_url, page_text). `data` (a dict) makes it a form POST."""
    headers = {'User-Agent': 'Mozilla/5.0'}
    if cookie:
        headers['Cookie'] = f'REVEL_SESSION={cookie}'
    body = urllib.parse.urlencode(data).encode() if data is not None else None
    if body:
        headers['Content-Type'] = 'application/x-www-form-urlencoded'
        headers['Referer'] = url
        headers['Origin'] = BASE
    req = urllib.request.Request(url, data=body, headers=headers)
    try:
        with urllib.request.urlopen(req, timeout=20) as r:
            return r.geturl(), r.read().decode('utf-8', 'replace')
    except urllib.error.HTTPError as e:
        return url, f'HTTP {e.code}'
    except urllib.error.URLError as e:
        raise click.ClickException(f'Could not reach AtCoder: {e.reason}')


def username(page):
    m = re.search(r'userScreenName\s*=\s*"([^"]*)"', page)
    return m.group(1) if m else ''


# ---------- Problems ----------

def parse_samples(page):
    """Return [(input, output), ...] from a task page (English section if present)."""
    i = page.find('class="lang-en"')
    section = page[i:] if i != -1 else page
    found = {}
    for kind, num, text in re.findall(
            r'<h3>\s*(Sample Input|Sample Output|入力例|出力例)\s*(\d+).*?</h3>\s*<pre[^>]*>(.*?)</pre>',
            section, re.S):
        key = 'in' if kind in ('Sample Input', '入力例') else 'out'
        text = html.unescape(re.sub(r'<[^>]+>', '', text)).replace('\r\n', '\n')
        found.setdefault(int(num), {}).setdefault(key, text)
    return [(v.get('in', ''), v.get('out', '')) for _, v in sorted(found.items())]


def setup_problem(config, contest, task_id, tests, url):
    """Create the problem folder; never overwrites an existing sol.cpp."""
    letter = task_id.rsplit('_', 1)[-1].upper()
    folder = AtCoder.problem_dir(config, contest, letter, single=False)
    folder.mkdir(parents=True, exist_ok=True)
    sol = folder / 'sol.cpp'
    if not sol.exists():
        shutil.copy2(AtCoder.template(config), sol)
    for i, (inp, out) in enumerate(tests, 1):
        (folder / f'in{i}.txt').write_text(inp if inp.endswith('\n') else inp + '\n')
        (folder / f'out{i}.txt').write_text(out if out.endswith('\n') else out + '\n')
    AtCoder.save_meta(folder, contest, task_id, url)
    return folder


def task_ids(contest, cookie):
    _, page = fetch(f'{BASE}/contests/{contest}/tasks', cookie)
    ids = re.findall(rf'href="/contests/{re.escape(contest)}/tasks/([^"/?#]+)"', page)
    return list(dict.fromkeys(ids))  # unique, in page order


# ---------- CLI ----------

@click.group()
def cli():
    """AtCoder helper - login, fetch samples, submit."""


@cli.command()
def login():
    """Save your AtCoder session cookie so `ac submit` can submit as you."""
    click.echo('AtCoder login has a CAPTCHA, so log in in your browser, then:\n'
               'DevTools (Cmd+Opt+I) -> Application -> Cookies -> https://atcoder.jp -> copy REVEL_SESSION.')
    session = click.prompt('REVEL_SESSION', hide_input=True).strip()
    AUTH_FILE.parent.mkdir(parents=True, exist_ok=True)
    AUTH_FILE.write_text(json.dumps({'session': session}))
    AUTH_FILE.chmod(0o600)
    name = username(fetch(f'{BASE}/home', session)[1])
    if name:
        print_success(f'Logged in as {name}')
    else:
        print_error('Cookie saved, but AtCoder says you are not logged in. Check the value and retry.')


@cli.command()
@click.argument('contest')
@click.argument('problem', required=False)
def get(contest, problem):
    """Fetch samples without the browser: `ac get abc400` or `ac get abc400 c` (or a task URL)."""
    parsed = AtCoder.parse(contest)
    if parsed:  # a task URL was given
        contest, problem, _ = parsed
    contest = contest.lower()
    config = config_for(AtCoder)
    cookie = load_cookie()

    ids = task_ids(contest, cookie)
    if not ids:
        raise click.ClickException(f'No tasks found for {contest} (wrong ID, or the contest has not started).')
    if problem:
        ids = [t for t in ids if t.rsplit('_', 1)[-1].upper() == problem.upper()]
        if not ids:
            raise click.ClickException(f'{contest} has no problem {problem.upper()}.')

    sols = []
    for task_id in ids:
        url = f'{BASE}/contests/{contest}/tasks/{task_id}'
        tests = parse_samples(fetch(url, cookie)[1])
        folder = setup_problem(config, contest, task_id, tests, url)
        sols.append(folder / 'sol.cpp')
        print_success(f'✓ {folder.name}: {task_id} ({len(tests)} samples)')

    target = sols[0].parent if problem else AtCoder.root(config) / contest
    print_info(f'Directory: {target}')
    request_cd(target)
    open_in_editor(target, sols)


@cli.group()
def contest():
    """Contest commands."""


@contest.command('listen')
def contest_listen():
    """Receive a whole contest from Competitive Companion."""
    from .listen import main
    main(AtCoder)


@cli.group()
def problem():
    """Single problem commands."""


@problem.command('listen')
def problem_listen():
    """Receive one problem from Competitive Companion."""
    from .problem_listen import main
    main(AtCoder)


# ---------- Submit ----------

def find_problem(problem, contest_id):
    """Return (contest, task_id, folder)."""
    cwd = Path.cwd()
    if problem:
        folder = (AtCoder.root(load_config()) / contest_id if contest_id else cwd) / problem.upper()
    else:
        folder = cwd
    meta = folder / '.ac.json'
    if meta.exists():
        info = json.loads(meta.read_text())
        return info['contest'], info['task_id'], folder
    contest = contest_id or folder.parent.name
    print_warning('No .ac.json here; guessing the task ID from the folder names.')
    return contest, f'{contest}_{folder.name.lower()}', folder


def pick_language(page):
    start = page.find('name="data.LanguageId"')
    block = page[start:page.find('</select>', start)] if start != -1 else ''
    options = [(v, html.unescape(t).strip())
               for v, t in re.findall(r'<option value="(\d+)"[^>]*>([^<]+)</option>', block)]
    if not options:
        return None
    wanted = load_config().get('atcoder_language')
    for pattern in ([re.escape(wanted)] if wanted else []) + [r'C\+\+.*gcc', r'C\+\+']:
        for value, text in options:
            if re.search(pattern, text, re.I):
                return value, text
    return options[0]


def submissions(contest, cookie):
    """Newest-first list of dicts: id, task, status, time, memory."""
    _, page = fetch(f'{BASE}/contests/{contest}/submissions/me', cookie)
    body = page[page.find('<tbody>'):page.find('</tbody>')]
    rows = []
    for row in re.findall(r'<tr>(.*?)</tr>', body, re.S):
        sid = re.search(r'/submissions/(\d+)"', row)
        status = re.search(r'<span[^>]*class=["\']label[^>]*>([^<]*)</span>', row)
        if not sid or not status:
            continue
        task = re.search(r'/tasks/([^"/?#]+)"', row)
        t = re.search(r'>(\d+\s*ms)<', row)
        m = re.search(r'>(\d+\s*KiB)<', row)
        rows.append({'id': int(sid.group(1)), 'task': task.group(1) if task else '',
                     'status': status.group(1).strip(),
                     'time': t.group(1) if t else '', 'memory': m.group(1) if m else ''})
    return rows


def latest_id(contest, cookie):
    rows = submissions(contest, cookie)
    return rows[0]['id'] if rows else 0


def wait_for_verdict(contest, task_id, cookie, after_id, timeout=300):
    print_info('Waiting for the verdict...')
    deadline = time.time() + timeout
    shown = None
    while time.time() < deadline:
        rows = [r for r in submissions(contest, cookie) if r['id'] > after_id and r['task'] == task_id]
        if rows:
            r = rows[0]
            pending = r['status'] in ('WJ', 'WR') or re.match(r'\d+\s*/\s*\d+', r['status'])
            if not pending:
                line = f"{r['status']}  {r['time']}  {r['memory']}  ({BASE}/contests/{contest}/submissions/{r['id']})"
                (print_success if r['status'] == 'AC' else print_error)(line)
                return
            if r['status'] != shown:
                shown = r['status']
                print_info(f'  {shown}')
        time.sleep(2)
    print_warning('Still judging; check the submissions page.')


@cli.command()
@click.argument('problem', required=False)
@click.option('-c', '--contest', 'contest_id', default=None, help='Contest ID, e.g. abc400')
def submit(problem, contest_id):
    """Submit sol.cpp: `ac submit A` in a contest folder, or `ac submit` in a problem folder."""
    contest, task_id, folder = find_problem(problem, contest_id)
    sol = folder / 'sol.cpp'
    if not sol.exists():
        raise click.ClickException(f'{sol} not found.')
    code = sol.read_text()
    submit_url = f'{BASE}/contests/{contest}/submit?taskScreenName={task_id}'
    cookie = load_cookie()
    print_info(f'Submitting {task_id} ({contest})')

    after_id = 0
    submitted = False
    logged_in = False
    if cookie:
        final_url, page = fetch(submit_url, cookie)
        if '/login' in final_url or not username(page):
            print_warning('Session expired or not logged in (run `ac login`). Falling back to the browser.')
        else:
            logged_in = True
            after_id = latest_id(contest, cookie)
            csrf = re.search(r'name="csrf_token" value="([^"]+)"', page)
            lang = pick_language(page)
            if csrf and lang:
                print_info(f'Language: {lang[1]}')
                final_url, _ = fetch(f'{BASE}/contests/{contest}/submit', cookie, {
                    'data.TaskScreenName': task_id, 'data.LanguageId': lang[0],
                    'sourceCode': code, 'csrf_token': csrf.group(1)})
                submitted = '/submissions/me' in final_url
                if submitted:
                    print_success('Submitted.')
                else:
                    print_warning('AtCoder did not accept the scripted submit. Falling back to the browser.')
            else:
                print_warning('Could not read the submit form. Falling back to the browser.')

    if not submitted:
        subprocess.run(['pbcopy'], input=code, text=True, check=False)
        webbrowser.open(submit_url)
        print_info('sol.cpp is on your clipboard: paste it in the browser and click Submit.')
        if not logged_in:
            print_warning('Run `ac login` to see verdicts here.')
            return

    wait_for_verdict(contest, task_id, cookie, after_id)
