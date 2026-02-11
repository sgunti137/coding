# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a competitive programming workspace containing:
- **cf-helper**: A Python CLI tool for Codeforces contest automation
- **Contests/**: Active Codeforces contest problems
- **Leetcode/**: LeetCode problems organized by difficulty (Easy/Medium/Hard)
- **AdventOfCode/**: Advent of Code solutions
- **Algorithms/**: Algorithm implementations
- **Data Structures and Algorithms/**: DSA implementations
- **Threads/**: Multithreading examples

## CF Helper Tool

### Installation
```bash
cd cf-helper
pip install -e .
```

This installs `cf`, `start`, `addtest`, and `run` commands globally.

### Two Modes: Contest vs Individual Problems

**Contest Mode:** Setup entire contests with multiple problems (A, B, C, ...)
**Problem Mode:** Setup single problems for random practice

### Configuration
Config file: `~/.cfhelper/config.yaml`
- First run will prompt for template path and base directory
- Default template: `/Contests/template.cpp`
- Default base: `/Contests`
- Compiler flags: `-std=c++17 -O2 -Wall`

### Contest Workflow (Multiple Problems)
```bash
# 1. Start listener in terminal
cf contest listen

# 2. In browser: Navigate to contest page and click Competitive Companion extension
#    This automatically creates directories, copies templates, and saves test cases

# 3. Navigate to contest directory (printed in output)
cd /Contests/1974

# 4. Test solution (run detects problem directories in current folder)
run A                    # Tests A/sol.cpp
run B -d                 # Test B with debug output
run C                    # Test C
```

### Problem Workflow (Single Problem Practice)
```bash
# 1. Start listener in terminal
cf problem listen

# 2. In browser: Navigate to problem page (e.g., codeforces.com/problemset/problem/2194/B)
#    Click Competitive Companion extension
#    Creates folder: /Contests/2194B/
#    Listener stops immediately after receiving problem!

# 3. Navigate to problem directory
cd /Contests/2194B

# 4. Solve and test (no problem argument needed!)
vim sol.cpp
run                      # Automatically detects problem directory
run -d                   # Test with debug output
```

### Alternative Workflow (Manual)
```bash
# 1. Setup contest structure
start 1974                # Creates /Contests/1974/{A,B,C,...}

# 2. Navigate to contest directory
cd /Contests/1974

# 3. Add test cases manually
addtest A                 # Paste input, Ctrl+D, paste output, Ctrl+D
addtest B

# 4. Test solution
run A                     # Tests A/sol.cpp
run B -d                  # Test B with debug output
```

**Note:** You can also use `-c` flag to run from anywhere: `run A -c 1974`

### Competitive Companion Integration (NEW)

**Browser Extension Setup:**
1. Install Competitive Companion:
   - Chrome: [Chrome Web Store](https://chromewebstore.google.com/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl)
   - Firefox: [Mozilla Add-ons](https://addons.mozilla.org/en-US/firefox/addon/competitive-companion/)

2. Usage:
   ```bash
   # Terminal: Start listener
   cf contest listen

   # Browser: Go to contest page (e.g., codeforces.com/contest/1974)
   # Click Competitive Companion icon
   # All problems automatically set up!
   ```

**How it works:**
- `cf contest listen` runs HTTP server on localhost:10043
- Competitive Companion parses problem page in browser (no bot detection)
- Sends JSON with test cases to listener
- Listener creates directories, copies templates, saves test cases
- Ready to solve immediately!

**Benefits:**
- No HTTP 403 errors (runs in authenticated browser)
- One click to set up entire contest
- Faster than manual `addtest` workflow
- Works with all Codeforces problems

### Important Notes
- **Recommended:** Use `cf contest listen` + Competitive Companion for fastest setup
- **Directory-based workflow:** Always `cd` into contest directory (`cd /Contests/1974`) before running commands
- **No active contest tracking:** Commands (`run`, `addtest`) automatically detect problem folders in current directory
- **Override with `-c` flag:** Run from anywhere using `run A -c 1974` or `addtest A -c 1974`
- **Fallback:** Use `addtest` command to manually add test cases by pasting from problem page
- Test files are named: `in1.txt`, `out1.txt`, `in2.txt`, `out2.txt`, etc.

## C++ Template System

Template location: `/Contests/template.cpp`

### Key Features
- Debug macro system using `#ifndef ONLINE_JUDGE`
- Debug output goes to stderr (won't affect solution output)
- Template includes:
  - `debug() << ...` for formatted debug output
  - `imie(variable)` macro for variable inspection
  - Auto-formatting for pairs, ranges, and containers

### Template Structure
```cpp
void test_case() {
    // Implement solution here
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        test_case();
    }
    return 0;
}
```

### Debug Usage
```cpp
debug() << imie(x) << imie(arr);  // Only prints when not ONLINE_JUDGE
```

## Compilation & Execution

### Using runSettings.json
The `runSettings.json` file defines compilation and run commands for different languages:

**C++:**
```bash
g++ file.cpp -o file
./file
```

**Python:**
```bash
python file.py
```

**Java:**
```bash
javac file.java
java -cp directory ClassName
```

### Manual Compilation
```bash
g++ -std=c++17 -O2 -Wall solution.cpp -o solution
./solution < input.txt
```

## Directory Structure

### Contests Directory
After running `start <contest-id>`, creates:
```
/Contests/
├── <contest-id>/
│   ├── A/
│   │   ├── sol.cpp      # Template copy
│   │   ├── in1.txt      # Test input
│   │   ├── out1.txt     # Expected output
│   │   └── ...
│   ├── B/
│   └── ...
├── template.cpp         # Main template
├── gen.cpp             # Test generator utility
└── tarzan.cpp          # Utility file
```

### Problem Categories
- **Leetcode/Easy/**: Easy LeetCode problems
- **Leetcode/Medium/**: Medium LeetCode problems
- **Leetcode/Hard/**: Hard LeetCode problems
- **AdventOfCode/**: Solutions named `Day1.cpp`, `Day2.cpp`, etc.

## Common Operations

### Setting Up a Contest
```bash
# Method 1: Using Competitive Companion (RECOMMENDED)
cf contest listen         # Start listener, then click extension in browser

# Method 2: Manual test case entry
start <contest-id>        # Create structure (test scraping will fail)
addtest A                 # Add test cases by pasting

# Method 3: Create test files directly
# Create in1.txt with input, out1.txt with expected output
# Increment numbers for additional tests
```

### Testing Solutions
```bash
# From within contest directory (/Contests/1974/)
run A                     # Tests ./A/sol.cpp
run B -d                  # Test B with debug output
run C                     # Test C

# From anywhere using -c flag
run A -c 1974             # Tests /Contests/1974/A/sol.cpp
```

### Working with Multiple Contests
Simply `cd` into the contest directory you want to work on:
```bash
cd /Contests/1974
run A

cd /Contests/2025
run A
```

Or use the `-c` flag from anywhere: `run A -c 2025`

## File Organization

- Contest solutions use subdirectory structure: `/Contests/<contest-id>/<problem>/sol.cpp`
- Standalone practice files can exist in root of `/Contests/` directory
- Both structures coexist without interference
- Each contest problem directory is self-contained with solution and test cases

## Troubleshooting

### HTTP 403 During Contest Setup
Normal and expected when using `start` command - Codeforces blocks automated scraping. **Solution:** Use `listen` + Competitive Companion instead.

### Port Already in Use (listen command)
If you see "Port 10043 is already in use", another tool (CP Editor, CPH) is using the same port. Close it first or use a different tool.

### Competitive Companion Not Sending Data
- Ensure `listen` command is running in terminal
- Check you clicked the extension icon while on contest/problem page
- Try reloading the browser page and clicking again

### No Active Contest Error
Run `start <contest-id>` or use `listen` + Competitive Companion to initialize contest structure.

### Compilation Errors
Check compiler configuration in `~/.cfhelper/config.yaml`. Default uses g++ with C++17.

### Test Case Mismatches
The test runner normalizes trailing whitespace and line endings. Ensure output format matches expected output exactly.
