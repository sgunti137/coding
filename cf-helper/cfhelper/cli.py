"""Main CLI entry point for CF Helper"""

import click
from .listen import main as listen_main
from .problem_listen import main as problem_listen_main


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


if __name__ == '__main__':
    cli()
