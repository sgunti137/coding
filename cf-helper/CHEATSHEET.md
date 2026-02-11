# CF Helper - Cheat Sheet

## Quick Reference

### Setup Contest
```bash
start 1974                    # Create directory structure
```

### Add Test Cases (RECOMMENDED)
```bash
addtest A                     # Interactive: paste input/output
addtest A -n 2                # Add specific test number
addtest A -c 1974             # Specify different contest
```

### Test Solution
```bash
run A                         # Test current active contest
run A -c 1974                 # Test specific contest
run A -d                      # Show debug output (stderr)
```

### Manual Test Cases
```bash
# Create files directly
cd /Contests/1974/A
echo "4\n3 1 4 2" > in1.txt
echo "4" > out1.txt
```

## Typical Workflow

```bash
# 1. Setup
start 1974

# 2. Open problem in browser
# https://codeforces.com/contest/1974/problem/A

# 3. Add test cases
addtest A      # Paste test 1
addtest A      # Paste test 2

# 4. Solve
vim /Contests/1974/A/sol.cpp

# 5. Test
run A
```

## Test Output Colors

- ✓ GREEN = Test passed
- ✗ RED = Test failed (shows diff)
- RED = Compilation error (shows g++ output)
- YELLOW = Runtime error or timeout

## Directory Structure

```
/Contests/1974/
├── A/
│   ├── sol.cpp      # Your template (edit this)
│   ├── in1.txt      # Test input 1
│   ├── out1.txt     # Expected output 1
│   ├── in2.txt      # Test input 2
│   └── out2.txt     # Expected output 2
├── B/
├── C/
...
```

## Configuration

Location: `~/.cfhelper/config.yaml`

```yaml
template_path: /path/to/template.cpp
base_dir: /path/to/Contests
compiler: g++
compile_flags: ['-std=c++17', '-O2', '-Wall']
active_contest: 1974
timeout: 2.0
```

## Common Issues

| Issue | Solution |
|-------|----------|
| HTTP 403 (scraping fails) | Use `addtest` - this is normal |
| No active contest | Run `start <contest-id>` first |
| Compilation error | Check g++ output and fix syntax |
| Tests not found | Use `addtest` to create test files |

## Tips

1. **Debug output is ignored**: Your debug statements (using `cerr`) won't affect test results
2. **See debug output**: Use `run A -d` to show debug output when needed
3. **Test cases auto-increment**: Just run `addtest A` multiple times
4. **Press Ctrl+D** to finish pasting (not Enter)
5. **Use `-c` flag** to test different contests without changing active contest
6. **Whitespace is normalized** - trailing spaces won't cause failures
7. **2-second timeout** per test case (configurable in config)

## Commands

| Command | What It Does |
|---------|--------------|
| `start 1974` | Setup contest 1974 structure |
| `addtest A` | Add test case to problem A |
| `run A` | Compile and test problem A |
| `run A -c 1974` | Test A from contest 1974 |

## Getting Help

- Full docs: [README.md](README.md)
- Scraping issues: [WORKAROUNDS.md](WORKAROUNDS.md)
- Quick start: [QUICKSTART.md](QUICKSTART.md)
- Implementation: [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md)
