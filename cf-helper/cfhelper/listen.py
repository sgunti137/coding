"""Listen command - Receive problems from Competitive Companion browser extension"""

import json
import re
import shutil
import time
from http.server import HTTPServer, BaseHTTPRequestHandler
from pathlib import Path
from typing import Optional, Tuple

from .config import load_config, save_config, is_first_run, prompt_first_time_setup
from .utils import print_success, print_error, print_info, print_warning


class CompetitiveCompanionHandler(BaseHTTPRequestHandler):
    """HTTP handler for receiving data from Competitive Companion"""

    # Track contest info across requests
    contest_id = None
    problems_received = []
    last_received_time = None
    server_instance = None

    def log_message(self, format, *args):
        """Suppress default HTTP server logs"""
        pass

    def do_POST(self):
        """Handle POST request from Competitive Companion"""
        try:
            # Read JSON data
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))

            # Parse problem data
            success = self.process_problem(data)

            if success:
                self.send_response(200)
            else:
                self.send_response(400)

            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'OK' if success else b'ERROR')

        except Exception as e:
            print_error(f"Error processing request: {e}")
            self.send_response(500)
            self.end_headers()

    def extract_contest_and_problem(self, url: str) -> Optional[Tuple[int, str]]:
        """Extract contest ID and problem letter from URL

        Examples:
            https://codeforces.com/contest/1974/problem/A -> (1974, 'A')
            https://codeforces.com/contest/1974/problem/F1 -> (1974, 'F1')
            https://codeforces.com/problemset/problem/1974/A -> (1974, 'A')
        """
        # Try contest URL format (matches A, B, F1, F2, etc.)
        match = re.search(r'/contest/(\d+)/problem/([A-Z]\d*)', url)
        if match:
            return (int(match.group(1)), match.group(2))

        # Try problemset URL format (matches A, B, F1, F2, etc.)
        match = re.search(r'/problemset/problem/(\d+)/([A-Z]\d*)', url)
        if match:
            return (int(match.group(1)), match.group(2))

        return None

    def process_problem(self, data: dict) -> bool:
        """Process a single problem from Competitive Companion"""
        # Extract info from JSON
        url = data.get('url', '')
        name = data.get('name', 'Unknown')
        tests = data.get('tests', [])

        # Parse contest and problem
        parsed = self.extract_contest_and_problem(url)
        if not parsed:
            print_error(f"Could not parse URL: {url}")
            return False

        contest_id, problem_letter = parsed

        # Track contest ID (set on first problem)
        if CompetitiveCompanionHandler.contest_id is None:
            CompetitiveCompanionHandler.contest_id = contest_id
            print_info(f"\nReceiving contest {contest_id}...")

        # Verify all problems are from same contest
        if contest_id != CompetitiveCompanionHandler.contest_id:
            print_warning(f"Problem {problem_letter} is from different contest ({contest_id}), skipping...")
            return False

        # Load config
        config = load_config()
        template_path = config['template_path']
        base_dir = config['base_dir']

        # Validate paths
        if not Path(template_path).exists():
            print_error(f"Template file not found: {template_path}")
            return False

        if not Path(base_dir).exists():
            print_error(f"Base directory not found: {base_dir}")
            return False

        # Create problem directory
        contest_dir = Path(base_dir) / str(contest_id)
        problem_dir = contest_dir / problem_letter
        problem_dir.mkdir(parents=True, exist_ok=True)

        # Copy template to sol.cpp
        sol_path = problem_dir / 'sol.cpp'
        shutil.copy2(template_path, sol_path)

        # Save test cases
        for i, test in enumerate(tests, start=1):
            input_text = test.get('input', '')
            output_text = test.get('output', '')

            input_file = problem_dir / f'in{i}.txt'
            output_file = problem_dir / f'out{i}.txt'

            with open(input_file, 'w') as f:
                f.write(input_text)
                if not input_text.endswith('\n'):
                    f.write('\n')

            with open(output_file, 'w') as f:
                f.write(output_text)
                if not output_text.endswith('\n'):
                    f.write('\n')

        # Track received problems
        CompetitiveCompanionHandler.problems_received.append(problem_letter)
        CompetitiveCompanionHandler.last_received_time = time.time()

        # Print success
        print_success(f"✓ Problem {problem_letter}: {name} ({len(tests)} test cases)")

        return True


def should_stop(timeout_seconds=5):
    """Check if we should stop the server due to timeout"""
    if CompetitiveCompanionHandler.last_received_time is None:
        return False

    elapsed = time.time() - CompetitiveCompanionHandler.last_received_time
    return elapsed >= timeout_seconds


def print_summary(config):
    """Print completion summary"""
    print()
    print("=" * 60)
    if CompetitiveCompanionHandler.problems_received:
        contest_id = CompetitiveCompanionHandler.contest_id
        problems = ', '.join(CompetitiveCompanionHandler.problems_received)
        contest_dir = Path(config['base_dir']) / str(contest_id)

        print_success(f"\nContest {contest_id} setup complete!")
        print_info(f"Problems received: {problems}")
        print_info(f"Directory: {contest_dir}")
        print()
        print_warning("Next steps:")
        print(f"  cd {contest_dir}")
        print(f"  run A")
    else:
        print_warning("\nNo problems received.")
    print("=" * 60)


def main():
    """Start HTTP server to listen for Competitive Companion"""
    # First-time setup if needed
    if is_first_run():
        prompt_first_time_setup()

    config = load_config()

    # Validate config
    if not Path(config['template_path']).exists():
        print_error(f"Template file not found: {config['template_path']}")
        print_error("Please update your config at ~/.cfhelper/config.yaml")
        return

    if not Path(config['base_dir']).exists():
        print_error(f"Base directory not found: {config['base_dir']}")
        print_error("Please update your config at ~/.cfhelper/config.yaml")
        return

    # Reset state
    CompetitiveCompanionHandler.contest_id = None
    CompetitiveCompanionHandler.problems_received = []
    CompetitiveCompanionHandler.last_received_time = None

    # Start server
    port = 10043  # Default Competitive Companion port
    timeout_seconds = 5  # Auto-stop after 5 seconds of inactivity

    print("=" * 60)
    print_info("CF Helper - Competitive Companion Listener")
    print("=" * 60)
    print_info(f"Listening on http://localhost:{port}")
    print_info("Waiting for problems from Competitive Companion...")
    print()
    print_warning("Instructions:")
    print("  1. Go to Codeforces contest page in your browser")
    print("  2. Click the Competitive Companion extension icon")
    print("  3. Problems will be automatically set up")
    print()
    print_warning(f"Auto-stops after {timeout_seconds}s of inactivity (or press Ctrl+C)")
    print("=" * 60)
    print()

    server = None
    try:
        server = HTTPServer(('localhost', port), CompetitiveCompanionHandler)
        CompetitiveCompanionHandler.server_instance = server

        # Set timeout for polling
        server.timeout = 1.0

        # Serve with timeout checking
        while True:
            server.handle_request()

            # Check if we should stop due to timeout
            if should_stop(timeout_seconds):
                print()
                print_info(f"No new problems for {timeout_seconds} seconds. Auto-stopping...")
                break

    except KeyboardInterrupt:
        print()
        print_info("Stopped by user.")
    except OSError as e:
        print()
        if "Address already in use" in str(e):
            print_error(f"Port {port} is already in use!")
            print_error("Another program (like CP Editor or CPH) might be running.")
            print_error(f"Close it and try again, or change the port.")
        else:
            print_error(f"Error starting server: {e}")
        return
    finally:
        if server:
            server.server_close()
        print_summary(config)


if __name__ == '__main__':
    main()
