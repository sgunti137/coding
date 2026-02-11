"""Start command - Setup contest directory structure"""

import os
import shutil
from pathlib import Path
import click

from .config import load_config, is_first_run, prompt_first_time_setup
from .api import CodeforcesAPI
from .utils import print_success, print_error, print_info, print_warning


@click.command()
@click.argument('contest_id', type=int)
def main(contest_id):
    """Setup a Codeforces contest directory structure (without test cases)

    Use 'cf contest listen' with Competitive Companion for automatic test case setup,
    or use 'addtest' to manually add test cases after running this command.
    """

    # First-time setup if needed
    if is_first_run():
        prompt_first_time_setup()

    config = load_config()
    template_path = config['template_path']
    base_dir = config['base_dir']

    # Validate paths
    if not os.path.exists(template_path):
        print_error(f"Template file not found: {template_path}")
        print_error("Please update your config at ~/.cfhelper/config.yaml")
        exit(1)

    if not os.path.exists(base_dir):
        print_error(f"Base directory not found: {base_dir}")
        print_error("Please update your config at ~/.cfhelper/config.yaml")
        exit(1)

    # Validate contest
    print_info(f"Fetching contest {contest_id}...")
    if not CodeforcesAPI.validate_contest(contest_id):
        print_error(f"Contest {contest_id} not found or is not accessible")
        exit(1)

    # Get problem list
    problem_letters = CodeforcesAPI.get_contest_problems(contest_id)
    if not problem_letters:
        print_error("Failed to fetch problem list. The contest might not exist or is not accessible.")
        exit(1)

    print_success(f"Found {len(problem_letters)} problems: {', '.join(problem_letters)}")

    # Create contest directory
    contest_dir = Path(base_dir) / str(contest_id)
    if contest_dir.exists():
        print_info(f"Contest directory already exists: {contest_dir}")
        overwrite = input("Overwrite? (y/n): ").strip().lower()
        if overwrite != 'y':
            print("Cancelled.")
            exit(0)
        # Remove existing directory
        shutil.rmtree(contest_dir)

    print_info("Creating directory structure...")
    contest_dir.mkdir(parents=True, exist_ok=True)

    # Create problem directories
    for letter in problem_letters:
        problem_dir = contest_dir / letter
        problem_dir.mkdir(exist_ok=True)

        # Copy template to sol.cpp
        sol_path = problem_dir / 'sol.cpp'
        shutil.copy2(template_path, sol_path)

    print()
    print_success(f"Contest {contest_id} setup complete!")
    print_info(f"Directory: {contest_dir}")
    print()
    print_warning("Note: Test cases not included. Add them using:")
    print(f"  1. Recommended: Use 'cf contest listen' + Competitive Companion")
    print(f"  2. Manual: cd {contest_dir} && addtest A")
    print()
    print_warning("Next steps:")
    print(f"  cd {contest_dir}")
    print(f"  addtest A  # Add test cases manually")
    print(f"  run A      # Test your solution")


if __name__ == '__main__':
    main()
