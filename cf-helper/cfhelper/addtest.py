"""Add test command - Manually add test cases to a problem"""

import click
from pathlib import Path

from .config import load_config
from .utils import print_success, print_error, print_info


@click.command()
@click.argument('problem', type=str)
@click.option('-c', '--contest', type=int, default=None, help='Contest ID (uses current directory or active contest if not specified)')
@click.option('-n', '--number', type=int, default=None, help='Test case number (auto-increments if not specified)')
def main(problem, contest, number):
    """Add a test case to a problem by pasting input and output"""

    config = load_config()
    problem_upper = problem.upper()

    # Determine problem directory
    if contest is not None:
        # Explicit contest ID provided
        base_dir = config['base_dir']
        contest_dir = Path(base_dir) / str(contest)
        problem_dir = contest_dir / problem_upper
    else:
        # Check if current directory has problem folders
        cwd = Path.cwd()
        potential_problem_dir = cwd / problem_upper

        if potential_problem_dir.exists():
            # We're in a contest directory!
            problem_dir = potential_problem_dir
        else:
            # Fall back to active contest
            contest = config.get('active_contest')
            if contest is None:
                print_error("No problem found in current directory and no active contest set.")
                print_error("Either:")
                print_error("  1. Run from a contest directory (cd /Contests/<contest-id>)")
                print_error("  2. Use -c flag: addtest A -c <contest-id>")
                print_error("  3. Set up a contest first: start <contest-id>")
                exit(1)

            base_dir = config['base_dir']
            contest_dir = Path(base_dir) / str(contest)
            problem_dir = contest_dir / problem_upper

    if not problem_dir.exists():
        print_error(f"Problem directory not found: {problem_dir}")
        exit(1)

    # Determine test case number
    if number is None:
        # Find next available test number
        existing_tests = list(problem_dir.glob('in*.txt'))
        if existing_tests:
            numbers = [int(f.stem[2:]) for f in existing_tests]
            number = max(numbers) + 1
        else:
            number = 1

    input_file = problem_dir / f'in{number}.txt'
    output_file = problem_dir / f'out{number}.txt'

    if input_file.exists():
        print_error(f"Test case {number} already exists")
        overwrite = input("Overwrite? (y/n): ").strip().lower()
        if overwrite != 'y':
            print("Cancelled.")
            exit(0)

    # Get input from user
    print_info(f"Adding test case {number} for problem {problem.upper()}")
    print()
    print("Paste the INPUT (press Ctrl+D when done, or Ctrl+C to cancel):")

    try:
        input_lines = []
        while True:
            try:
                line = input()
                input_lines.append(line)
            except EOFError:
                break
    except KeyboardInterrupt:
        print("\nCancelled.")
        exit(0)

    input_text = '\n'.join(input_lines)

    print()
    print("Paste the EXPECTED OUTPUT (press Ctrl+D when done, or Ctrl+C to cancel):")

    try:
        output_lines = []
        while True:
            try:
                line = input()
                output_lines.append(line)
            except EOFError:
                break
    except KeyboardInterrupt:
        print("\nCancelled.")
        exit(0)

    output_text = '\n'.join(output_lines)

    # Save test case
    with open(input_file, 'w') as f:
        f.write(input_text)
        if not input_text.endswith('\n'):
            f.write('\n')

    with open(output_file, 'w') as f:
        f.write(output_text)
        if not output_text.endswith('\n'):
            f.write('\n')

    print()
    print_success(f"✓ Test case {number} added successfully!")
    print_info(f"Input: {input_file}")
    print_info(f"Output: {output_file}")
    print()
    print_info(f"Run 'run {problem.upper()}' to test your solution")


if __name__ == '__main__':
    main()
