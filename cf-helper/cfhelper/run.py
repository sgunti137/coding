"""Run command - Compile and test solutions"""

import os
import subprocess
import time
from pathlib import Path
import click

from .config import load_config
from .utils import (
    print_success, print_error, print_warning, print_info,
    normalize_output, format_diff
)


@click.command()
@click.argument('problem', type=str, required=False)
@click.option('-c', '--contest', type=int, default=None, help='Contest ID (uses current directory or active contest if not specified)')
@click.option('-d', '--debug', is_flag=True, help='Show debug output (stderr)')
def main(problem, contest, debug):
    """Compile and test a solution against sample test cases"""

    config = load_config()
    cwd = Path.cwd()

    # Determine problem directory
    if problem is None:
        # No problem argument - check if we're in a problem directory
        if (cwd / 'sol.cpp').exists() and list(cwd.glob('in*.txt')):
            # We're in a problem directory!
            problem_dir = cwd
        else:
            print_error("No problem specified and not in a problem directory.")
            print_error("Either:")
            print_error("  1. Run 'run' from a problem directory (/Contests/2194B/)")
            print_error("  2. Run 'run A' from a contest directory (/Contests/1974/)")
            print_error("  3. Use: run A -c <contest-id>")
            exit(1)
    else:
        problem_upper = problem.upper()

        if contest is not None:
            # Explicit contest ID provided
            base_dir = config['base_dir']
            contest_dir = Path(base_dir) / str(contest)
            problem_dir = contest_dir / problem_upper
        else:
            # Check if current directory has problem folders (A/, B/, C/, etc.)
            potential_problem_dir = cwd / problem_upper

            if potential_problem_dir.exists() and (potential_problem_dir / 'sol.cpp').exists():
                # We're in a contest directory!
                problem_dir = potential_problem_dir
            else:
                # Fall back to active contest
                contest = config.get('active_contest')
                if contest is None:
                    print_error("No problem found in current directory and no active contest set.")
                    print_error("Either:")
                    print_error("  1. Run from a contest directory (cd /Contests/<contest-id>)")
                    print_error("  2. Use -c flag: run A -c <contest-id>")
                    print_error("  3. Set up a contest first: start <contest-id>")
                    exit(1)

                base_dir = config['base_dir']
                contest_dir = Path(base_dir) / str(contest)
                problem_dir = contest_dir / problem_upper

    if not problem_dir.exists():
        print_error(f"Problem directory not found: {problem_dir}")
        exit(1)

    sol_cpp = problem_dir / 'sol.cpp'
    if not sol_cpp.exists():
        print_error(f"Solution file not found: {sol_cpp}")
        exit(1)

    # Compile
    if problem is None:
        print(f"\033[96mCompiling sol.cpp...\033[0m", end=' ', flush=True)
    else:
        print(f"\033[96mCompiling {problem.upper()}/sol.cpp...\033[0m", end=' ', flush=True)

    compiler = config.get('compiler', 'g++')
    compile_flags = config.get('compile_flags', ['-std=c++17', '-O2', '-Wall'])
    output_binary = problem_dir / 'sol'

    compile_cmd = [compiler] + compile_flags + [str(sol_cpp), '-o', str(output_binary)]

    try:
        result = subprocess.run(
            compile_cmd,
            capture_output=True,
            text=True,
            cwd=problem_dir
        )

        if result.returncode != 0:
            print_error("✗")
            print_error("Compilation failed:")
            print(result.stderr)
            exit(1)

        print_success("✓")
    except Exception as e:
        print_error("✗")
        print_error(f"Compilation error: {e}")
        exit(1)

    # Find test cases
    test_files = sorted(problem_dir.glob('in*.txt'))
    if not test_files:
        print_warning("No test cases found")
        exit(0)

    print_info("Running tests...")
    if not debug:
        print_info("(Debug output ignored - use -d flag to show)\n")
    else:
        print_info("(Showing debug output from stderr)\n")

    # Run tests
    passed = 0
    failed = 0
    timeout_limit = config.get('timeout', 2.0)
    test_times = []  # Store (test_num, time_taken, status)

    for input_file in test_files:
        # Determine test number from filename (in1.txt -> 1)
        test_num = input_file.stem[2:]  # Remove 'in' prefix
        output_file = problem_dir / f'out{test_num}.txt'

        if not output_file.exists():
            print_warning(f"Test {test_num}: No expected output file")
            continue

        # Read test case
        with open(input_file, 'r') as f:
            test_input = f.read()

        with open(output_file, 'r') as f:
            expected_output = f.read()

        # Run solution
        try:
            start_time = time.time()
            result = subprocess.run(
                [str(output_binary)],
                input=test_input,
                capture_output=True,
                text=True,
                timeout=timeout_limit,
                cwd=problem_dir
            )
            end_time = time.time()
            time_taken = (end_time - start_time) * 1000  # Convert to milliseconds

            if result.returncode != 0:
                print_error(f"Test {test_num}: RUNTIME ERROR ✗ ({time_taken:.0f}ms)")
                test_times.append((test_num, time_taken, "RUNTIME ERROR"))
                if result.stderr:
                    print(f"  Error output:\n{result.stderr}")
                failed += 1
                continue

            # Compare output (only stdout, stderr/debug is ignored)
            actual_output = result.stdout
            expected_normalized = normalize_output(expected_output)
            actual_normalized = normalize_output(actual_output)

            if expected_normalized == actual_normalized:
                print_success(f"Test {test_num}: PASSED ✓ ({time_taken:.0f}ms)")
                test_times.append((test_num, time_taken, "PASSED"))
                # Show debug output if requested
                if debug and result.stderr:
                    print(f"  Debug output:")
                    for line in result.stderr.strip().split('\n'):
                        print(f"    {line}")
                passed += 1
            else:
                print_error(f"Test {test_num}: FAILED ✗ ({time_taken:.0f}ms)")
                test_times.append((test_num, time_taken, "FAILED"))
                print(format_diff(expected_normalized, actual_normalized))
                # Show debug output if requested
                if debug and result.stderr:
                    print(f"  Debug output:")
                    for line in result.stderr.strip().split('\n'):
                        print(f"    {line}")
                failed += 1

        except subprocess.TimeoutExpired:
            time_taken = timeout_limit * 1000  # Timeout in ms
            print_error(f"Test {test_num}: TIMEOUT ✗ (exceeded {timeout_limit}s)")
            test_times.append((test_num, time_taken, "TIMEOUT"))
            failed += 1

        except Exception as e:
            print_error(f"Test {test_num}: ERROR ✗")
            print(f"  {e}")
            test_times.append((test_num, 0, "ERROR"))
            failed += 1

    # Summary
    total = passed + failed
    print()
    if failed == 0:
        print_success(f"Summary: All {passed} tests passed! ✓")
    else:
        print_info(f"Summary: {passed}/{total} tests passed")

    # Timing summary
    if test_times:
        print()
        print_info("Execution times:")
        total_time = 0
        for test_num, time_ms, status in test_times:
            total_time += time_ms
            status_color = "\033[92m" if status == "PASSED" else "\033[91m"  # Green for pass, red for others
            print(f"  Test {test_num}: {status_color}{time_ms:.0f}ms\033[0m")
        print(f"  Total: {total_time:.0f}ms")


if __name__ == '__main__':
    main()
