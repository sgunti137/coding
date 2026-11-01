"""lc - fetch LeetCode problems and test C++ solutions locally"""

import html
import os
import json
import re
import subprocess
import time
import urllib.error
import urllib.request
from pathlib import Path

import click

from .config import load_config
from .utils import print_success, print_error, print_warning, print_info, format_diff

GRAPHQL = 'https://leetcode.com/graphql'
RUNTIME = Path(__file__).parent / 'lc_runtime.h'

HEADER = """#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <climits>
#include <cmath>
using namespace std;

"""


def gql(query, variables=None):
    body = json.dumps({'query': query, 'variables': variables or {}}).encode()
    req = urllib.request.Request(GRAPHQL, data=body, headers={
        'Content-Type': 'application/json',
        'Referer': 'https://leetcode.com',
        'User-Agent': 'Mozilla/5.0',
    })
    with urllib.request.urlopen(req, timeout=20) as r:
        return json.load(r)['data']


def resolve_slug(ref):
    m = re.search(r'leetcode\.com/problems/([\w-]+)', ref)
    if m:
        return m.group(1)
    if ref.isdigit():
        data = gql('query q($k:String){questionList(categorySlug:"",limit:20,skip:0,filters:{searchKeywords:$k})'
                   '{data{questionFrontendId titleSlug}}}', {'k': ref})
        for q in data['questionList']['data']:
            if q['questionFrontendId'] == ref:
                return q['titleSlug']
        raise click.ClickException(f'No problem with number {ref}')
    return ref.strip('/').lower()


def leetcode_dir():
    config = load_config()
    if config.get('leetcode_dir'):
        return Path(config['leetcode_dir'])
    return Path(config['base_dir']).parent / 'Leetcode'


def parse_outputs(content):
    text = re.sub(r'<[^>]+>', '', content or '')
    text = html.unescape(text)
    return [m.strip() for m in re.findall(r'Output:\s*(.+)', text)]


@click.group()
def cli():
    """LeetCode helper: lc get <problem>, then lc run inside the problem folder"""


@cli.command()
@click.argument('problem')
def get(problem):
    """Set up a problem. PROBLEM is a number (994), slug (rotting-oranges) or URL."""
    slug = resolve_slug(problem)
    q = gql('query q($s:String!){question(titleSlug:$s){questionId questionFrontendId title titleSlug difficulty '
            'exampleTestcases metaData content codeSnippets{langSlug code}}}', {'s': slug})['question']
    if not q:
        raise click.ClickException(f'Problem not found: {slug}')

    meta = json.loads(q['metaData'])
    folder = leetcode_dir() / q['difficulty'] / f"{q['questionFrontendId']}.{q['titleSlug']}"
    folder.mkdir(parents=True, exist_ok=True)

    sol = folder / 'sol.cpp'
    if sol.exists():
        print_warning(f'sol.cpp already exists, not overwriting')
    else:
        snippet = next((c['code'] for c in q['codeSnippets'] or [] if c['langSlug'] == 'cpp'), 'class Solution {\n};')
        link = f"// {q['questionFrontendId']}. {q['title']}\n// https://leetcode.com/problems/{q['titleSlug']}/\n\n"
        sol.write_text(HEADER + link + snippet + '\n')

    (folder / '.lc.json').write_text(json.dumps({
        'id': q['questionFrontendId'], 'question_id': q['questionId'], 'slug': q['titleSlug'], 'title': q['title'], 'meta': meta,
    }, indent=2))

    if 'classname' in meta:
        print_warning('Design problem (class with several methods): lc run does not support these yet.')
    else:
        lines = [l for l in (q['exampleTestcases'] or '').split('\n')]
        n = len(meta.get('params', [])) or 1
        cases = [lines[i:i + n] for i in range(0, len(lines), n)]
        outputs = parse_outputs(q['content'])
        if len(outputs) != len(cases):
            print_warning('Could not read expected outputs; tests will just show your output.')
            outputs = [None] * len(cases)
        for i, (inp, out) in enumerate(zip(cases, outputs), 1):
            (folder / f'in{i}.txt').write_text('\n'.join(inp) + '\n')
            if out is not None:
                (folder / f'out{i}.txt').write_text(out + '\n')
        print_success(f'{len(cases)} example test(s) saved')

    print_info(f"{q['questionFrontendId']}. {q['title']} ({q['difficulty']})")
    print(f'cd "{folder}"')
    try:
        if not os.environ.get('LC_NO_OPEN'):
            subprocess.run(['code', str(sol)], check=False)
    except FileNotFoundError:
        pass


def norm(s):
    return re.sub(r'\s+', '', s)


@cli.command()
@click.option('-d', '--debug', is_flag=True, help='Show stderr (debug prints)')
def run(debug):
    """Compile sol.cpp in the current folder and run it on in*.txt / out*.txt."""
    folder = Path.cwd()
    info_file = folder / '.lc.json'
    sol = folder / 'sol.cpp'
    if not sol.exists() or not info_file.exists():
        raise click.ClickException('Run this inside a folder made by `lc get`.')
    meta = json.loads(info_file.read_text())['meta']
    if 'classname' in meta:
        raise click.ClickException('Design problems are not supported by lc run yet.')

    config = load_config()
    harness = folder / '.harness.cpp'
    binary = folder / '.sol'
    harness.write_text(f'#include "{RUNTIME}"\n#include "sol.cpp"\n'
                       f'int main() {{ lc::run(&Solution::{meta["name"]}); }}\n')

    print('\033[96mCompiling sol.cpp...\033[0m', end=' ', flush=True)
    flags = config.get('compile_flags', ['-std=c++17', '-O2', '-Wall'])
    flags = [f for f in flags if not f.startswith('-std=')] + ['-std=c++17']
    res = subprocess.run([config.get('compiler', 'g++')] + flags + [str(harness), '-o', str(binary)],
                         capture_output=True, text=True, cwd=folder)
    if res.returncode != 0:
        print_error('✗')
        print(res.stderr.replace(str(harness), '.harness.cpp'))
        raise SystemExit(1)
    print_success('✓')

    def num(p):
        s = p.stem[2:]
        return int(s) if s.isdigit() else 0
    tests = sorted(folder.glob('in*.txt'), key=num)
    if not tests:
        print_warning('No tests (add in1.txt / out1.txt)')
        return

    passed = failed = 0
    timeout = config.get('timeout', 2.0)
    for inp in tests:
        n = inp.stem[2:]
        out = folder / f'out{n}.txt'
        try:
            t0 = time.time()
            r = subprocess.run([str(binary)], input=inp.read_text(), capture_output=True, text=True,
                               timeout=timeout, cwd=folder)
            ms = (time.time() - t0) * 1000
        except subprocess.TimeoutExpired as e:
            print_error(f'Test {n}: TIMEOUT ✗ (>{timeout}s)')
            print(f'  Input:\n    ' + inp.read_text().strip().replace('\n', '\n    '))
            for label, data in (('Output', e.stdout), ('Debug output (last 40 lines)', e.stderr)):
                if isinstance(data, bytes):
                    data = data.decode(errors='replace')
                if data and data.strip():
                    print(f'  {label} before timeout:')
                    for line in data.strip().split('\n')[-40:]:
                        print(f'    {line}')
            if not (e.stderr and e.stderr.strip()):
                print('  (No debug output. Add cerr << ... prints to see where it gets stuck.)')
            failed += 1
            continue

        got = r.stdout.strip()
        if r.returncode != 0:
            print_error(f'Test {n}: RUNTIME ERROR ✗ ({ms:.0f}ms)')
            if r.stderr:
                print(f'  {r.stderr.strip()}')
            failed += 1
            continue
        if not out.exists():
            print_info(f'Test {n}: (no expected output) ({ms:.0f}ms)')
            print(f'  Output: {got}')
        elif norm(got) == norm(out.read_text()):
            print_success(f'Test {n}: PASSED ✓ ({ms:.0f}ms)')
            passed += 1
        else:
            print_error(f'Test {n}: FAILED ✗ ({ms:.0f}ms)')
            print(f'  Input:\n    ' + inp.read_text().strip().replace('\n', '\n    '))
            print(format_diff(out.read_text().strip(), got))
            failed += 1
        if debug and r.stderr:
            print('  Debug output:')
            for line in r.stderr.strip().split('\n'):
                print(f'    {line}')

    print()
    total = passed + failed
    if total and failed == 0:
        print_success(f'All {passed} tests passed! ✓')
    elif total:
        print_info(f'{passed}/{total} tests passed')


@cli.command()
def add():
    """Add a custom test: paste input (one argument per line), Ctrl+D, then expected output, Ctrl+D."""
    folder = Path.cwd()
    if not (folder / '.lc.json').exists():
        raise click.ClickException('Run this inside a folder made by `lc get`.')
    n = 1
    while (folder / f'in{n}.txt').exists():
        n += 1
    click.echo('Input (one argument per line), then Ctrl+D:')
    import sys
    inp = sys.stdin.read()
    sys.stdin = open('/dev/tty')
    click.echo('Expected output (leave empty to skip), then Ctrl+D:')
    out = sys.stdin.read()
    (folder / f'in{n}.txt').write_text(inp.strip() + '\n')
    if out.strip():
        (folder / f'out{n}.txt').write_text(out.strip() + '\n')
    print_success(f'Saved test {n}')


AUTH_FILE = Path.home() / '.cfhelper' / 'leetcode.json'


def load_auth():
    if not AUTH_FILE.exists():
        raise click.ClickException('Not logged in. Run `lc login` first.')
    return json.loads(AUTH_FILE.read_text())


def lc_request(url, auth, referer, data=None):
    headers = {
        'Cookie': f"LEETCODE_SESSION={auth['session']}; csrftoken={auth['csrftoken']}",
        'X-CSRFToken': auth['csrftoken'],
        'Referer': referer,
        'Origin': 'https://leetcode.com',
        'User-Agent': 'Mozilla/5.0',
        'Content-Type': 'application/json',
    }
    body = json.dumps(data).encode() if data is not None else None
    req = urllib.request.Request(url, data=body, headers=headers, method='POST' if body else 'GET')
    try:
        with urllib.request.urlopen(req, timeout=20) as r:
            return json.load(r)
    except urllib.error.HTTPError as e:
        if e.code in (401, 403):
            raise click.ClickException(f'LeetCode refused the request (HTTP {e.code}). '
                                       'Your session may have expired: run `lc login` again.')
        raise click.ClickException(f'LeetCode error: HTTP {e.code}')


@cli.command()
def login():
    """Save your LeetCode browser cookies so `lc submit` can submit as you."""
    click.echo('In your browser, open leetcode.com (logged in) -> DevTools (Cmd+Opt+I) -> Application\n'
               '-> Cookies -> https://leetcode.com, and copy these two values.')
    session = click.prompt('LEETCODE_SESSION', hide_input=True).strip()
    csrf = click.prompt('csrftoken', hide_input=True).strip()
    AUTH_FILE.parent.mkdir(parents=True, exist_ok=True)
    AUTH_FILE.write_text(json.dumps({'session': session, 'csrftoken': csrf}))
    AUTH_FILE.chmod(0o600)
    auth = {'session': session, 'csrftoken': csrf}
    data = lc_request(GRAPHQL, auth, 'https://leetcode.com',
                      {'query': 'query{userStatus{isSignedIn username}}'})
    status = data.get('data', {}).get('userStatus') or {}
    if status.get('isSignedIn'):
        print_success(f"Logged in as {status['username']}")
    else:
        print_error('Cookies saved, but LeetCode says you are not signed in. Check the values and retry.')


@cli.command()
def submit():
    """Submit sol.cpp in the current folder to LeetCode and show the verdict."""
    folder = Path.cwd()
    info_file = folder / '.lc.json'
    sol = folder / 'sol.cpp'
    if not sol.exists() or not info_file.exists():
        raise click.ClickException('Run this inside a folder made by `lc get`.')
    info = json.loads(info_file.read_text())
    slug = info['slug']
    auth = load_auth()

    qid = info.get('question_id')
    if not qid:
        qid = gql('query q($s:String!){question(titleSlug:$s){questionId}}', {'s': slug})['question']['questionId']
        info['question_id'] = qid
        info_file.write_text(json.dumps(info, indent=2))

    referer = f'https://leetcode.com/problems/{slug}/'
    print_info(f"Submitting {info['id']}. {info['title']}...")
    res = lc_request(f'https://leetcode.com/problems/{slug}/submit/', auth, referer,
                     {'lang': 'cpp', 'question_id': str(qid), 'typed_code': sol.read_text()})
    sub_id = res.get('submission_id')
    if not sub_id:
        raise click.ClickException(f'Submit failed: {res}')

    for _ in range(60):
        time.sleep(1)
        r = lc_request(f'https://leetcode.com/submissions/detail/{sub_id}/check/', auth, referer)
        if r.get('state') == 'SUCCESS':
            break
    else:
        raise click.ClickException(f'Still judging. See https://leetcode.com/submissions/detail/{sub_id}/')

    verdict = r.get('status_msg', '?')
    print()
    if verdict == 'Accepted':
        print_success(f'Accepted ✓  {r.get("status_runtime")} (beats {r.get("runtime_percentile", 0):.1f}%), '
                      f'{r.get("status_memory")} (beats {r.get("memory_percentile", 0):.1f}%)')
    else:
        print_error(f'{verdict} ✗  ({r.get("total_correct")}/{r.get("total_testcases")} tests passed)')
        if r.get('full_compile_error') or r.get('compile_error'):
            print(r.get('full_compile_error') or r.get('compile_error'))
        if r.get('full_runtime_error') or r.get('runtime_error'):
            print(r.get('full_runtime_error') or r.get('runtime_error'))
        if r.get('last_testcase'):
            print('  Input:\n    ' + r['last_testcase'].strip().replace('\n', '\n    '))
            if r.get('expected_output') is not None:
                print(f"  Expected: {r['expected_output']}")
            if r.get('code_output') is not None:
                print(f"  Got:      {r['code_output']}")
            if click.confirm('Save this failing case as a local test?', default=True):
                n = 1
                while (folder / f'in{n}.txt').exists():
                    n += 1
                (folder / f'in{n}.txt').write_text(r['last_testcase'].strip() + '\n')
                if r.get('expected_output'):
                    (folder / f'out{n}.txt').write_text(r['expected_output'].strip() + '\n')
                print_success(f'Saved as test {n}')
    print(f'https://leetcode.com/submissions/detail/{sub_id}/')


if __name__ == '__main__':
    cli()
