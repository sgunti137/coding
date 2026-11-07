"""Utility functions for CF Helper"""

from colorama import Fore, Style, init as colorama_init

# Initialize colorama for cross-platform color support
colorama_init(autoreset=True)


def print_success(message: str):
    """Print success message in green"""
    print(f"{Fore.GREEN}{message}{Style.RESET_ALL}")


def print_error(message: str):
    """Print error message in red"""
    print(f"{Fore.RED}{message}{Style.RESET_ALL}")


def print_warning(message: str):
    """Print warning message in yellow"""
    print(f"{Fore.YELLOW}{message}{Style.RESET_ALL}")


def print_info(message: str):
    """Print info message in cyan"""
    print(f"{Fore.CYAN}{message}{Style.RESET_ALL}")


def normalize_output(text: str) -> str:
    """Normalize output for comparison"""
    # Strip trailing whitespace from each line and normalize line endings
    lines = text.replace('\r\n', '\n').split('\n')
    lines = [line.rstrip() for line in lines]
    # Remove trailing empty lines
    while lines and not lines[-1]:
        lines.pop()
    return '\n'.join(lines)


def format_diff(expected: str, got: str) -> str:
    """Format difference between expected and actual output"""
    result = []
    result.append("  Expected:")
    for line in expected.split('\n'):
        result.append(f"    {line}")
    result.append("  Got:")
    for line in got.split('\n'):
        result.append(f"    {line}")
    return '\n'.join(result)


SUBLIME_CLI = '/Applications/Sublime Text.app/Contents/SharedSupport/bin/subl'


def open_in_editor(folder, files=()):
    """Open folder in a new Sublime Text window with the given files; fall back to just the folder."""
    import os, shutil, subprocess
    if os.environ.get('CF_NO_OPEN') or os.environ.get('LC_NO_OPEN'):
        return
    cli = shutil.which('subl') or (SUBLIME_CLI if os.path.exists(SUBLIME_CLI) else None)
    try:
        if cli:
            subprocess.run([cli, '-n', str(folder), *map(str, files)], check=False)
        else:
            subprocess.run(['open', '-a', 'Sublime Text', str(folder)], check=False)
    except FileNotFoundError:
        pass


def request_cd(path):
    """Ask the shell wrapper (see ~/.zshrc) to cd into path after the command exits."""
    import os
    target = os.environ.get('CFHELPER_CD_FILE')
    if target:
        with open(target, 'w') as f:
            f.write(str(path))
    else:
        print(f'  cd "{path}"')
