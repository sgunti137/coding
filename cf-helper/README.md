# CF Helper - Codeforces Contest Setup and Testing Tool

A command-line tool to streamline your Codeforces competitive programming workflow. Set up directory structures, manage test cases, and test your solutions with colorized output.

## ⚠️ Important Note About Test Cases

Codeforces blocks automated test case scraping (HTTP 403). **Solution:** Use Competitive Companion browser extension with the `cf contest listen` command:

```bash
cf contest listen   # Start listener
                    # Click Competitive Companion in browser
run A               # Test your solution
```

**Alternative:** Use the `addtest` command to manually add test cases:

```bash
start 1974      # Setup contest structure
addtest A       # Add test case by pasting input/output
run A           # Test your solution
```

See [WORKAROUNDS.md](WORKAROUNDS.md) for detailed solutions.

## Features

- **Automatic Contest Setup**: Creates organized directory structure with your template
- **Easy Test Case Addition**: Interactive `addtest` command for adding test cases
- **Template Management**: Automatically copy your C++ template to each problem
- **Testing with Colors**: Run your solutions against test cases with colorized pass/fail output
- **Multiple Contests**: Easy switching between different contests
- **Fast Workflow**: Focus on solving problems instead of manual setup

## Installation

```bash
cd cf-helper
pip install -e .
```

After installation, `start` and `run` commands will be available globally.

## First-Time Setup

On first run, you'll be prompted to configure:
- Path to your C++ template file
- Base directory for contests

Configuration is stored in `~/.cfhelper/config.yaml` and can be edited manually.

## Two Modes of Operation

### Contest Mode (Multiple Problems)
Setup entire contests with multiple problems (A, B, C, ...)

### Problem Mode (Single Problem Practice)
Setup individual problems for random practice

## Competitive Companion Integration (NEW - Recommended!)

The easiest way to set up both contests and problems is using the **Competitive Companion** browser extension:

### Installation

**Chrome:** [Chrome Web Store](https://chromewebstore.google.com/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl)

**Firefox:** [Mozilla Add-ons](https://addons.mozilla.org/en-US/firefox/addon/competitive-companion/)

### Usage for Contests

```bash
# 1. Start listener
cf contest listen

# 2. In browser: Go to contest page (e.g., codeforces.com/contest/1974)
#    Click Competitive Companion extension icon

# 3. Navigate to contest directory (printed in output)
cd /Contests/1974

# 4. Solve and test
vim A/sol.cpp
run A
```

### Usage for Individual Problems

```bash
# 1. Start listener
cf problem listen

# 2. In browser: Go to problem page (e.g., codeforces.com/problemset/problem/2194/B)
#    Click Competitive Companion extension icon
#    Listener stops immediately after receiving the problem!

# 3. Navigate to problem directory (printed in output)
cd /Contests/2194B

# 4. Solve and test (no problem argument needed!)
vim sol.cpp
run
```

**Benefits:**
- ✅ No HTTP 403 errors
- ✅ One click to set up entire contest
- ✅ Automatically extracts all test cases
- ✅ Works with your browser's authenticated session

Press `Ctrl+C` to stop the listener after receiving problems.

## Usage

### Recommended Workflow (Competitive Companion)

```bash
# 1. Start listener
cf contest listen

# 2. Click Competitive Companion in browser on contest page

# 3. Navigate to contest directory
cd /Contests/1974

# 4. Solve and test
vim A/sol.cpp
run A
```

### Alternative Workflow (Manual)

```bash
# 1. Setup contest structure
start 1974

# 2. Navigate to contest directory
cd /Contests/1974

# 3. Add test cases interactively
addtest A
# Paste input, press Ctrl+D
# Paste output, press Ctrl+D

# 4. Solve and test
vim A/sol.cpp
run A
```

### Setup a Contest

```bash
start <contest-id>
```

Example:
```bash
start 1974
```

This will:
1. Validate the contest exists on Codeforces
2. Fetch all problems (A, B, C, D, etc.)
3. Create directory structure: `/Contests/1974/{A,B,C,D,...}/`
4. Copy your template to each problem as `sol.cpp`
5. Attempt to download sample test cases (may fail due to Codeforces blocking)
6. Set the contest as active

### Add Test Cases

Since Codeforces blocks automated scraping, use `addtest` to add test cases:

```bash
addtest <problem>
```

Example:
```bash
addtest A
```

This will:
1. Prompt you to paste the test input (press Ctrl+D when done)
2. Prompt you to paste the expected output (press Ctrl+D when done)
3. Save as the next available test case (in1.txt, in2.txt, etc.)
4. Auto-increment test numbers

You can also specify contest and test number:
```bash
addtest A -c 1974 -n 3  # Add test case 3 for problem A in contest 1974
```

### Test a Solution

```bash
run <problem>
```

Example:
```bash
run A           # Test with debug output hidden (default)
run A -d        # Test and show debug output (stderr)
run A -c 1974   # Test from different contest
```

This will:
1. Compile `A/sol.cpp` using g++ with your configured flags
2. Run the compiled binary against all test cases
3. Compare only stdout (debug output from stderr is ignored)
3. Display results with colors:
   - **GREEN ✓** for passed tests
   - **RED ✗** for failed tests (with diff)
   - **YELLOW** for runtime errors or timeouts

### Test Different Contest

```bash
run A -c 2025
```

This runs problem A from contest 2025 (instead of the active contest).

## Directory Structure

After running `start 1973`, your directory structure will be:

```
/Contests/
├── 1973/
│   ├── A/
│   │   ├── sol.cpp         # Your template
│   │   ├── in1.txt         # Sample input 1
│   │   ├── out1.txt        # Expected output 1
│   │   ├── in2.txt         # Sample input 2
│   │   └── out2.txt        # Expected output 2
│   ├── B/
│   │   └── ...
│   ├── C/
│   │   └── ...
│   └── D/
│       └── ...
└── template.cpp
```

## Configuration

Default configuration (`~/.cfhelper/config.yaml`):

```yaml
template_path: /path/to/your/template.cpp
base_dir: /path/to/Contests
compiler: g++
compile_flags:
  - -std=c++17
  - -O2
  - -Wall
active_contest: null
timeout: 2.0
```

You can edit this file to customize:
- Compiler and flags
- Timeout for test execution (in seconds)
- Default paths

## Example Workflow

```bash
# Setup contest structure
$ start 1974
Fetching contest 1974...
Found 7 problems: A, B, C, D, E, F, G
Creating directory structure...
Downloading test cases for A... HTTP 403
✗ (failed)
...
Contest 1974 setup complete!
Directory: /Contests/1974/
Active contest set to: 1974

Failed to download test cases for: A, B, C, D, E, F, G
You can manually add test cases as in1.txt/out1.txt, in2.txt/out2.txt, etc.
Or visit: https://codeforces.com/contest/1974

# Add test cases using addtest
$ addtest A
Adding test case 1 for problem A

Paste the INPUT (press Ctrl+D when done, or Ctrl+C to cancel):
4
3 1 4 2
[Ctrl+D]

Paste the EXPECTED OUTPUT (press Ctrl+D when done, or Ctrl+C to cancel):
4
[Ctrl+D]

✓ Test case 1 added successfully!

# Edit A/sol.cpp to solve the problem
# Then test it:

$ run A
Compiling A/sol.cpp... ✓
Running tests...

Test 1: PASSED ✓
Test 2: PASSED ✓
Test 3: FAILED ✗
  Expected:
    5
  Got:
    6

Summary: 2/3 tests passed
```

## Requirements

- Python 3.7+
- g++ (or another C++ compiler)
- Internet connection (for fetching contests)

## Troubleshooting

**"HTTP 403" when downloading test cases**: This is normal. Codeforces blocks automated scraping. Use `addtest` to add test cases manually. See [WORKAROUNDS.md](WORKAROUNDS.md) for details.

**"Contest not found"**: The contest ID might be invalid, or the contest is not yet public.

**"No test cases found"**: Use `addtest` to add test cases manually.

**"Compilation failed"**: Check your compiler configuration in `~/.cfhelper/config.yaml`.

## Commands Summary

### Contest Commands
| Command | Description |
|---------|-------------|
| `cf contest listen` | Listen for entire contest from Competitive Companion (RECOMMENDED) |
| `start <contest-id>` | Setup contest directory structure with templates |

### Problem Commands
| Command | Description |
|---------|-------------|
| `cf problem listen` | Listen for single problem from Competitive Companion (RECOMMENDED) |

### Testing Commands
| Command | Description |
|---------|-------------|
| `run` | Run tests (when in problem directory) |
| `run <problem>` | Run tests for specific problem (when in contest directory) |
| `run -d` | Test and show debug output (stderr) |
| `run <problem> -c <contest-id>` | Test a solution from a different contest |
| `addtest <problem>` | Interactively add test cases by pasting input/output |

## Documentation

- [README.md](README.md) - This file, main documentation
- [QUICKSTART.md](QUICKSTART.md) - Quick start guide for first-time users
- [WORKAROUNDS.md](WORKAROUNDS.md) - Solutions for test case scraping issues (HTTP 403)
- [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) - Technical implementation details

## Notes

- This tool creates a subdirectory structure (`/Contests/1973/A/`) and doesn't interfere with any existing flat files (`a.cpp`, `b.cpp`) in your Contests directory
- Test case comparison normalizes trailing whitespace and line endings
- The tool respects Codeforces by adding rate limiting between requests

## Future Enhancements

Potential features for future versions:
- Watch mode for auto-recompilation
- Stress testing against brute force solutions
- Direct submission to Codeforces
- Support for other platforms (AtCoder, Leetcode)

## License

MIT License
