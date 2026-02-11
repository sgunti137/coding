# Competitive Companion Integration Guide

## Quick Setup

### 1. Install Browser Extension

**Chrome:**
- Visit [Chrome Web Store](https://chromewebstore.google.com/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl)
- Click "Add to Chrome"

**Firefox:**
- Visit [Mozilla Add-ons](https://addons.mozilla.org/en-US/firefox/addon/competitive-companion/)
- Click "Add to Firefox"

### 2. Start the Listener

Open a terminal and run:
```bash
cf contest listen
```

You should see:
```
============================================================
CF Helper - Competitive Companion Listener
============================================================
Listening on http://localhost:10043
Waiting for problems from Competitive Companion...

Instructions:
  1. Go to Codeforces contest page in your browser
  2. Click the Competitive Companion extension icon
  3. Problems will be automatically set up

Auto-stops after 5s of inactivity (or press Ctrl+C)
============================================================
```

### 3. Parse Contest from Browser

**For entire contest (recommended):**
1. Navigate to: `https://codeforces.com/contest/1974`
2. Click the Competitive Companion icon in browser toolbar
3. All problems (A, B, C, D, ...) are parsed and sent

**For single problem:**
1. Navigate to: `https://codeforces.com/contest/1974/problem/A`
2. Click the Competitive Companion icon
3. Only problem A is parsed and sent

### 4. Watch Terminal Output

As each problem is received, you'll see:
```
Receiving contest 1974...
✓ Problem A: Problem Title (3 test cases)
✓ Problem B: Problem Title (2 test cases)
✓ Problem C: Problem Title (4 test cases)
...
```

### 5. Automatic Completion

The listener will **automatically stop** 5 seconds after receiving the last problem. You'll see:
```
No new problems for 5 seconds. Auto-stopping...

============================================================

Contest 1974 setup complete!
Problems received: A, B, C, D, E, F, G
Directory: /Contests/1974
Active contest set to: 1974

You can now use 'run <problem>' to test your solutions!
============================================================
```

**Note:** You can also press `Ctrl+C` anytime to stop manually.

### 6. Start Solving!

```bash
# Navigate to contest directory
cd /Contests/1974

# Edit solution
vim A/sol.cpp

# Test solution
run A
```

## How It Works

```
┌─────────────────────────────────────────────────────┐
│  Browser (Codeforces Contest Page)                  │
│                                                      │
│  User clicks Competitive Companion extension        │
└───────────────────┬─────────────────────────────────┘
                    │ HTTP POST with JSON
                    │ (contest, problem, test cases)
                    ▼
┌─────────────────────────────────────────────────────┐
│  Terminal (cf contest listen command)               │
│                                                      │
│  HTTP Server on localhost:10043                     │
│  Receives problem data                              │
└───────────────────┬─────────────────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────────────┐
│  File System                                        │
│                                                      │
│  Creates: /Contests/1974/A/                         │
│    ├── sol.cpp (from template)                      │
│    ├── in1.txt                                      │
│    ├── out1.txt                                     │
│    ├── in2.txt                                      │
│    └── out2.txt                                     │
└─────────────────────────────────────────────────────┘
```

## JSON Format Received

Competitive Companion sends data like:
```json
{
  "name": "A. Problem Title",
  "group": "Codeforces - Round #950 (Div. 3)",
  "url": "https://codeforces.com/contest/1974/problem/A",
  "timeLimit": 1000,
  "memoryLimit": 256,
  "tests": [
    {
      "input": "4\n3 1 4 2\n",
      "output": "4\n"
    },
    {
      "input": "5\n1 2 3 4 5\n",
      "output": "15\n"
    }
  ],
  "testType": "single"
}
```

The `listen` command:
1. Extracts contest ID (1974) and problem letter (A) from URL
2. Creates `/Contests/1974/A/` directory
3. Copies `template.cpp` to `sol.cpp`
4. Saves each test as `in1.txt`, `out1.txt`, `in2.txt`, `out2.txt`, etc.

## Troubleshooting

### Port Already in Use

**Error:**
```
Port 10043 is already in use!
Another program (like CP Editor or CPH) might be running.
```

**Solution:**
Close other competitive programming tools (CP Editor, CPH, etc.) that use port 10043.

### Extension Not Sending Data

**Problem:** Clicked extension but nothing happens in terminal.

**Solutions:**
1. Ensure `cf contest listen` command is running
2. Check browser console for errors (F12 → Console)
3. Verify extension is installed and enabled
4. Try reloading the page
5. Make sure you're on a Codeforces contest/problem page

### Wrong Contest/Problem Parsed

**Problem:** Extension parsed wrong problem.

**Solution:**
The listener extracts contest/problem from the URL. Make sure you're on the correct page before clicking the extension icon.

### Multiple Contests

**Problem:** Want to parse problems from different contests.

**Solution:**
Stop the listener (Ctrl+C) after each contest, then restart `listen` for the next contest. The tool prevents mixing problems from different contests in a single session.

## Advantages Over Manual Methods

| Feature | `cf contest listen` + Extension | `start` command | `addtest` command |
|---------|--------------------------------|-----------------|-------------------|
| One-click setup | ✅ Yes | ❌ No | ❌ No |
| No HTTP 403 | ✅ Yes | ❌ No | ✅ Yes |
| Speed | ⚡ Fastest | 🐢 Slow | 🐌 Slowest |
| Manual input | ❌ No | ❌ No | ✅ Yes |
| Works offline | ❌ No | ❌ No | ✅ Yes |

## Tips

1. **Parse entire contest:** Navigate to contest page (not individual problem) before clicking extension
2. **Auto-stops after 5 seconds:** The listener automatically stops when no new problems are received for 5 seconds
3. **Keep terminal visible:** Watch for confirmation that problems were received
4. **Use with virtual contests:** Works with both live and virtual contests
5. **Multiple attempts:** If parsing fails, you can click the extension again
6. **Verify test cases:** After setup, check `in1.txt`/`out1.txt` to ensure correct parsing

## Port Configuration

Default port: **10043** (Competitive Companion default for custom tools)

Other tools use different ports:
- CP Editor: 10045
- CPH: 27121
- Caide: 10043

If you need to change the port, edit `listen.py` line 235:
```python
port = 10043  # Change this value
```
