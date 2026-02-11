# CF Helper - Quick Start Guide

## Installation

```bash
cd cf-helper
pip install -e .
```

## First Use

The first time you run `start`, you'll be prompted to enter:
1. Path to your C++ template file (default: `/mnt/c/Users/saakethgunti/Development Work/coding/Contests/template.cpp`)
2. Base directory for contests (default: `/mnt/c/Users/saakethgunti/Development Work/coding/Contests`)

Or create `~/.cfhelper/config.yaml` manually with your settings.

## Basic Workflow

### 1. Setup a Contest

```bash
start 1974
```

This creates:
- Directory: `/Contests/1974/`
- Subdirectories: `A/`, `B/`, `C/`, etc.
- Each contains: `sol.cpp` (your template)

**Note**: Test case scraping usually fails (HTTP 403). Use `addtest` instead (see next step).

### 2. Add Test Cases

Since Codeforces blocks automated scraping, use `addtest`:

```bash
addtest A
```

Then:
1. Paste the test input (copy from problem page)
2. Press `Ctrl+D`
3. Paste the expected output
4. Press `Ctrl+D`

Repeat for each test case. They auto-increment (in1.txt, in2.txt, etc.).

### 3. Solve a Problem

Edit the `test_case()` function in `1974/A/sol.cpp`:

```cpp
void test_case() {
    int n;
    cin >> n;
    cout << n * 2 << "\n";
}
```

### 4. Test Your Solution

```bash
run A
```

Output:
```
Compiling A/sol.cpp... ✓
Running tests...

Test 1: PASSED ✓
Test 2: PASSED ✓
Test 3: FAILED ✗
  Expected:
    10
  Got:
    12

Summary: 2/3 tests passed
```

## Common Issues

### Test Cases Not Downloaded (HTTP 403)

This is **normal and expected**. Codeforces blocks automated scraping.

**Solution**: Use the `addtest` command:

```bash
addtest A
# Paste input from problem page
# Press Ctrl+D
# Paste output from problem page
# Press Ctrl+D
```

Or manually create test case files:
- `A/in1.txt` - First test input
- `A/out1.txt` - First test expected output
- `A/in2.txt` - Second test input
- `A/out2.txt` - Second test expected output
- etc.

See [WORKAROUNDS.md](WORKAROUNDS.md) for more solutions.

### No Active Contest

If you run `run A` without setting up a contest first:

```
No active contest. Run 'start <contest-id>' first
```

**Solution**: Run `start <contest-id>` to set up a contest.

### Compilation Errors

The tool shows full g++ error messages:

```
Compiling A/sol.cpp... ✗
Compilation failed:
/path/to/sol.cpp:34:9: error: expected initializer before 'cin'
```

**Solution**: Fix the syntax errors in your code.

## Tips

1. **Multiple Contests**: The tool tracks the active contest. Use `run A -c 1974` to test a different contest.

2. **Manual Test Cases**: You can add your own test cases - just create `in3.txt`, `out3.txt`, etc.

3. **Existing Files**: Your existing flat files (`a.cpp`, `b.cpp`) in `/Contests/` won't be touched. Both structures coexist.

4. **Config Location**: Edit `~/.cfhelper/config.yaml` to change compiler flags, timeout, etc.

5. **Template Preserved**: Your template's debug macros and `#ifndef ONLINE_JUDGE` guards are preserved.

## Configuration

Edit `~/.cfhelper/config.yaml`:

```yaml
template_path: /path/to/template.cpp
base_dir: /path/to/Contests
compiler: g++
compile_flags:
  - -std=c++17
  - -O2
  - -Wall
active_contest: 1973
timeout: 2.0
```

## Commands Summary

| Command | Description |
|---------|-------------|
| `start <contest-id>` | Setup contest directory structure with templates |
| `addtest <problem>` | Interactively add test cases (paste input/output) |
| `run <problem>` | Compile and test a solution against test cases |
| `run <problem> -c <contest-id>` | Test a solution from a different contest |

## Example Session

```bash
# Setup contest
$ start 1974
Fetching contest 1974...
Found 7 problems: A, B, C, D, E, F, G
Creating directory structure...
Downloading test cases for A... HTTP 403
✗ (failed)
...
Contest 1974 setup complete!

Failed to download test cases for: A, B, C, D, E, F, G
You can manually add test cases as in1.txt/out1.txt, in2.txt/out2.txt, etc.

# Add test cases
$ addtest A
Paste the INPUT (press Ctrl+D when done):
4
3 1 4 2
[Ctrl+D]

Paste the EXPECTED OUTPUT (press Ctrl+D when done):
4
[Ctrl+D]

✓ Test case 1 added successfully!

# Solve problem A
$ cd /Contests/1973/A
$ vim sol.cpp
# ... write solution ...

# Test it
$ run A
Compiling A/sol.cpp... ✓
Running tests...
Test 1: PASSED ✓
Test 2: PASSED ✓
Test 3: PASSED ✓
Summary: All 3 tests passed! ✓

# Move to next problem
$ run B
Compiling B/sol.cpp... ✓
Running tests...
Test 1: FAILED ✗
...
```

## Directory Structure After Setup

```
/Contests/
├── 1973/
│   ├── A/
│   │   ├── sol.cpp
│   │   ├── in1.txt
│   │   ├── out1.txt
│   │   ├── in2.txt
│   │   └── out2.txt
│   ├── B/
│   │   └── ...
│   └── ...
├── a.cpp               # Your existing files (untouched)
├── b.cpp
└── template.cpp
```
