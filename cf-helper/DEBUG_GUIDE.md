# CF Helper - Debug Output Guide

## How Debug Output Works

Your C++ template uses `cerr` for debug output with the `#ifndef ONLINE_JUDGE` guard:

```cpp
struct debug {
#ifndef ONLINE_JUDGE
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
...
#else
sim dor(const c&) { ris; }
#endif
};
```

This means:
- Debug output goes to **stderr** (error stream)
- Your actual output goes to **stdout** (standard output)
- CF Helper only compares stdout when testing

## Result: Debug Output is Automatically Ignored

When you run tests, your debug statements **do not affect test results** at all!

### Example

```cpp
void test_case() {
    int n;
    cin >> n;
    debug() << "Input:" << imie(n);  // This goes to stderr
    cout << n * 2 << "\n";             // This goes to stdout (tested)
}
```

When you run `run A`:
- ✓ Only `n * 2` is compared with expected output
- ✓ Debug output is completely ignored
- ✓ Tests pass/fail based only on stdout

## Viewing Debug Output

By default, debug output is hidden. To see it:

```bash
run A -d
```

### Without -d flag (default):
```
Test 1: PASSED ✓
Test 2: FAILED ✗
  Expected:
    10
  Got:
    8
```

### With -d flag:
```
Test 1: PASSED ✓
  Debug output:
    Input: [n: 5]
    Result: [result: 10]

Test 2: FAILED ✗
  Expected:
    10
  Got:
    8
  Debug output:
    Input: [n: 4]
    Result: [result: 8]
```

## When to Use -d Flag

### Use `-d` when you want to:
1. **Debug failed tests** - See what values your code is processing
2. **Verify logic** - Check intermediate calculations
3. **Understand behavior** - See how your code processes each test case
4. **Find bugs** - Track down where things go wrong

### Don't use `-d` when:
1. **Running quick tests** - Default is cleaner and faster
2. **Just checking pass/fail** - You don't need the extra output
3. **Testing many problems** - Too much output gets noisy

## Debug Output Examples

### Basic Debug
```cpp
void test_case() {
    int n;
    cin >> n;
    debug() << imie(n);
    cout << n << "\n";
}
```

Output with `-d`:
```
Debug output:
  [n: 42]
```

### Multiple Values
```cpp
void test_case() {
    int a, b, c;
    cin >> a >> b >> c;
    debug() << imie(a) << imie(b) << imie(c);
    cout << a + b + c << "\n";
}
```

Output with `-d`:
```
Debug output:
  [a: 1]  [b: 2]  [c: 3]
```

### Arrays/Vectors
```cpp
void test_case() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int& x : v) cin >> x;
    debug() << imie(n) << imie(v);
    cout << accumulate(v.begin(), v.end(), 0) << "\n";
}
```

Output with `-d`:
```
Debug output:
  [n: 5]  [v: [1, 2, 3, 4, 5]]
```

### Intermediate Results
```cpp
void test_case() {
    int n;
    cin >> n;
    debug() << "Processing input:" << imie(n);

    int result = n * 2;
    debug() << "After doubling:" << imie(result);

    result += 10;
    debug() << "After adding 10:" << imie(result);

    cout << result << "\n";
}
```

Output with `-d`:
```
Debug output:
  Processing input: [n: 5]
  After doubling: [result: 10]
  After adding 10: [result: 20]
```

## Important Notes

### 1. Debug Output Never Affects Tests
Your debug statements can print anything - they won't cause test failures.

```cpp
cout << "Answer: " << 42 << "\n";     // BAD - affects test
debug() << "Answer: " << imie(42);    // GOOD - ignored in tests
```

### 2. Online Judge Behavior
When you submit to Codeforces:
- `ONLINE_JUDGE` is defined
- All debug statements become no-ops
- No performance penalty
- Works exactly like your local tests

### 3. Compilation
CF Helper compiles without `-DONLINE_JUDGE`, so debug output works locally.

### 4. Runtime Errors
If your code crashes, stderr is always shown (with or without `-d`):

```
Test 1: RUNTIME ERROR ✗
  Error output:
    Segmentation fault
```

## Best Practices

### DO:
- ✓ Use debug freely during development
- ✓ Leave debug statements in your code
- ✓ Use `imie()` macro for named values
- ✓ Debug intermediate calculations
- ✓ Use `-d` when investigating failures

### DON'T:
- ✗ Put output in cout if it's for debugging
- ✗ Remove all debug statements (they're free!)
- ✗ Worry about debug affecting performance
- ✗ Mix debug and actual output

## Example Workflow

```bash
# 1. Write solution with debug statements
vim A/sol.cpp

# 2. Test without debug output (clean view)
run A

# 3. If tests fail, rerun with debug
run A -d

# 4. Fix based on debug output

# 5. Test again
run A

# 6. Submit to Codeforces (debug auto-disabled)
```

## Summary

| Aspect | Behavior |
|--------|----------|
| Default (`run A`) | Debug output hidden |
| With flag (`run A -d`) | Debug output shown |
| Test comparison | Only stdout compared |
| On Codeforces | Debug disabled automatically |
| Performance | No impact in either mode |
| Runtime errors | stderr always shown |

**Key Takeaway**: Use debug statements freely! They're automatically ignored during testing and disabled on Codeforces. Use `-d` when you need to see them.
