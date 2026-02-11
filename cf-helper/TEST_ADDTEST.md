# Testing the addtest Command

## Quick Test

Create test input and output for problem A in contest 1974:

### Test Case 1
**Input:**
```
4
3 1 4 2
```

**Output:**
```
4
```

### Test Case 2
**Input:**
```
5
1 1 1 1 1
```

**Output:**
```
0
```

## How to Use

```bash
# Make sure contest 1974 is set up
cd /Contests/1974/A

# Add first test case
addtest A

# When prompted for INPUT, paste:
4
3 1 4 2
# Press Ctrl+D

# When prompted for OUTPUT, paste:
4
# Press Ctrl+D

# Add second test case (auto-increments to test 2)
addtest A

# When prompted for INPUT, paste:
5
1 1 1 1 1
# Press Ctrl+D

# When prompted for OUTPUT, paste:
0
# Press Ctrl+D

# Verify files were created
ls -la

# Should see:
# in1.txt, out1.txt, in2.txt, out2.txt
```
