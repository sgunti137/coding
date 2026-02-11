# CF Helper - Workarounds for Test Case Issues

## Problem: HTTP 403 When Scraping

Codeforces has anti-bot protection that blocks automated scraping. When you run `start`, you may see:

```
Downloading test cases for A... HTTP 403
✗ (failed)
```

This is expected behavior from Codeforces to prevent automated access.

## Solution 1: Use `addtest` Command (Recommended)

The easiest way to add test cases is with the new `addtest` command:

```bash
# Add test case by pasting
addtest A

# It will prompt you:
# 1. Paste the input (press Ctrl+D when done)
# 2. Paste the expected output (press Ctrl+D when done)
```

**Example workflow:**
```bash
# Setup contest (creates directories)
start 1974

# Open problem in browser
# Copy first test case input and output

# Add test case 1
addtest A
# Paste input, press Ctrl+D
# Paste output, press Ctrl+D

# Add test case 2
addtest A
# Paste input, press Ctrl+D
# Paste output, press Ctrl+D

# Test your solution
run A
```

## Solution 2: Manual File Creation

Create test case files manually in the problem directory:

```bash
cd /Contests/1974/A

# Create test case 1
cat > in1.txt << 'EOF'
3
1 2 3
EOF

cat > out1.txt << 'EOF'
6
EOF

# Create test case 2
cat > in2.txt << 'EOF'
5
10 20 30 40 50
EOF

cat > out2.txt << 'EOF'
150
EOF
```

## Solution 3: Copy from Browser

1. Open the problem on Codeforces
2. Copy test cases from the problem page
3. Create files:
   ```bash
   cd /Contests/1974/A
   vim in1.txt    # Paste input
   vim out1.txt   # Paste output
   ```

## Solution 4: Competitive Companion Integration (Advanced)

If you use the Competitive Companion browser extension:

1. The extension can export test cases as JSON
2. Create a simple parser script:

```python
#!/usr/bin/env python3
import json
import sys
from pathlib import Path

# Read JSON from Competitive Companion
data = json.load(sys.stdin)
problem_dir = Path(data['name'])
problem_dir.mkdir(exist_ok=True)

for i, test in enumerate(data['tests'], 1):
    with open(problem_dir / f'in{i}.txt', 'w') as f:
        f.write(test['input'])
    with open(problem_dir / f'out{i}.txt', 'w') as f:
        f.write(test['output'])

print(f"Created {len(data['tests'])} test cases")
```

## Solution 5: Wait and Retry

Sometimes Codeforces temporarily blocks IPs. Try:

1. Wait 5-10 minutes
2. Use a VPN or different network
3. Try during off-peak hours

## Why This Happens

Codeforces actively protects against automated scraping because:
- It reduces server load
- Prevents abuse
- Encourages users to visit their site

This is completely reasonable and expected behavior.

## Best Practice Workflow

Since scraping is unreliable, here's the recommended workflow:

```bash
# 1. Setup contest structure (always works)
start 1974
# Creates directories, copies templates

# 2. Open problem in browser
# Visit: https://codeforces.com/contest/1974/problem/A

# 3. Add test cases using addtest (interactive)
addtest A
# Paste first test case

addtest A
# Paste second test case

# 4. Solve and test
run A
```

## File Format

Test case files are simple text files:

**in1.txt** (input):
```
3
1 2 3
```

**out1.txt** (expected output):
```
6
```

Each file should end with a newline. The tool handles whitespace normalization automatically.

## Testing Without Sample Cases

You can also:
1. Write your solution
2. Add your own test cases (even if they're not the official samples)
3. Test locally before submitting

The `run` command works with any test cases you provide.

## Summary

| Method | Pros | Cons |
|--------|------|------|
| `addtest` command | Interactive, easy | Manual for each test |
| Manual file creation | Full control | Most manual work |
| Browser copy | Direct from source | Copy-paste each time |
| Competitive Companion | Automatic | Requires extension |
| Wait and retry | No extra work | May not work |

**Recommendation**: Use `addtest` for quick manual addition, or create a personal Competitive Companion parser if you solve many problems.
