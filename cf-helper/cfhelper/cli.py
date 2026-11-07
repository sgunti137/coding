"""Main CLI entry point for CF Helper"""

import click
from .listen import main as listen_main
from .problem_listen import main as problem_listen_main
from .submit import main as submit_main


@click.group()
def cli():
    """CF Helper - Codeforces Contest Setup and Testing Tool"""
    pass


@cli.group()
def contest():
    """Contest management commands"""
    pass


@contest.command('listen')
def contest_listen():
    """Listen for problems from Competitive Companion browser extension"""
    listen_main()


@cli.group()
def problem():
    """Individual problem commands"""
    pass


@problem.command('listen')
def problem_listen():
    """Listen for a single problem from Competitive Companion browser extension"""
    problem_listen_main()


@cli.command()
@click.argument('contest', required=False)
@click.argument('problem', required=False)
def get(contest, problem):
    """Set up whatever you click in Competitive Companion.

    `cf get` just listens: click the extension on a contest page (-> Contests/<id>/A, B, ...)
    or on a problem / problemset page (-> Contests/<id><letter>).
    `cf get 2194`, `cf get 2194 B` or a URL also opens that page in the browser first.
    """
    if contest:
        import re
        import webbrowser
        m = (re.search(r'/contest/(\d+)(?:/problem/(\w+))?', contest)
             or re.search(r'/problemset/problem/(\d+)/(\w+)', contest))
        if m:
            contest, problem = m.group(1), problem or m.group(2)
        if not contest.isdigit():
            raise click.ClickException(f'Not a Codeforces contest ID or URL: {contest}')
        url = f'https://codeforces.com/contest/{contest}'
        if problem:
            url += f'/problem/{problem.upper()}'
        click.echo(f'Opening {url}')
        webbrowser.open(url)
    click.echo('Click the Competitive Companion icon on a Codeforces contest or problem page.')
    listen_main(auto=True)


cli.add_command(submit_main, 'submit')


if __name__ == '__main__':
    cli()
