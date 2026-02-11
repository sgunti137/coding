# CF Helper - Documentation Index

## Quick Links

### Getting Started
- [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) - **NEW! Recommended setup** using browser extension
- [QUICKSTART.md](QUICKSTART.md) - Basic setup and workflow
- [CHEATSHEET.md](CHEATSHEET.md) - Quick reference card for all commands

### Main Documentation
- [README.md](README.md) - Complete documentation with all features
- [DEBUG_GUIDE.md](DEBUG_GUIDE.md) - How debug output works (it's automatically ignored!)
- [SOLUTION_SUMMARY.md](SOLUTION_SUMMARY.md) - How the HTTP 403 issue was resolved

### Problem Solving
- [WORKAROUNDS.md](WORKAROUNDS.md) - Solutions for test case scraping issues (HTTP 403)
- [TEST_ADDTEST.md](TEST_ADDTEST.md) - How to use the addtest command

### Technical
- [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) - Technical implementation details

## Document Descriptions

### COMPETITIVE_COMPANION_GUIDE.md
**Purpose**: Setup using Competitive Companion browser extension (RECOMMENDED)
**Contains**: Extension installation, listener usage, troubleshooting
**Read if**: You want the easiest and fastest contest setup method

### QUICKSTART.md
**Purpose**: Get started quickly
**Contains**: Installation, basic workflow, common issues
**Read if**: First time using the tool

### CHEATSHEET.md
**Purpose**: Quick command reference
**Contains**: All commands, typical workflow, tips
**Read if**: You know the tool but need a reminder

### README.md
**Purpose**: Complete documentation
**Contains**: All features, detailed usage, configuration
**Read if**: You want comprehensive information

### WORKAROUNDS.md
**Purpose**: Solve HTTP 403 scraping issues
**Contains**: 5 different solutions for adding test cases
**Read if**: Test case scraping fails (it usually does)

### SOLUTION_SUMMARY.md
**Purpose**: Understand how the HTTP 403 issue was fixed
**Contains**: Problem description, solution details, new workflow
**Read if**: You want to understand the addtest command

### TEST_ADDTEST.md
**Purpose**: Learn to use addtest command
**Contains**: Test cases for practice, step-by-step guide
**Read if**: You want to practice using addtest

### IMPLEMENTATION_SUMMARY.md
**Purpose**: Technical details for developers
**Contains**: Package structure, implementation details, testing
**Read if**: You want to understand the codebase

## Common Questions → Documentation

| Question | Read This |
|----------|-----------|
| How do I get started? | [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) ⭐ |
| What's the fastest setup method? | [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) ⭐ |
| What commands are available? | [CHEATSHEET.md](CHEATSHEET.md) |
| How does debug output work? | [DEBUG_GUIDE.md](DEBUG_GUIDE.md) |
| HTTP 403 error when scraping? | [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) or [WORKAROUNDS.md](WORKAROUNDS.md) |
| How do I add test cases? | [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md), [WORKAROUNDS.md](WORKAROUNDS.md), [TEST_ADDTEST.md](TEST_ADDTEST.md) |
| How does addtest work? | [SOLUTION_SUMMARY.md](SOLUTION_SUMMARY.md) |
| What are all the features? | [README.md](README.md) |
| How is it implemented? | [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) |

## Reading Order

### For New Users (Recommended)
1. [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) - ⭐ Start here for easiest setup
2. [CHEATSHEET.md](CHEATSHEET.md) - Keep as reference

### For Users Without Browser Extension
1. [QUICKSTART.md](QUICKSTART.md) - Learn the basics
2. [WORKAROUNDS.md](WORKAROUNDS.md) - Understand test case addition
3. [CHEATSHEET.md](CHEATSHEET.md) - Keep as reference

### For Experienced Users
1. [CHEATSHEET.md](CHEATSHEET.md) - Quick command reference
2. [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) - Upgrade to faster workflow

### For Developers
1. [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) - Technical overview
2. [SOLUTION_SUMMARY.md](SOLUTION_SUMMARY.md) - HTTP 403 solution details
3. Source code in `cfhelper/` directory

## File Structure

```
cf-helper/
├── INDEX.md                      # This file
├── README.md                     # Main documentation
├── COMPETITIVE_COMPANION_GUIDE.md # ⭐ Browser extension guide
├── QUICKSTART.md                 # Quick start guide
├── CHEATSHEET.md                 # Quick reference
├── WORKAROUNDS.md                # HTTP 403 solutions
├── SOLUTION_SUMMARY.md           # How HTTP 403 was fixed
├── TEST_ADDTEST.md               # addtest command guide
├── DEBUG_GUIDE.md                # Debug output guide
├── IMPLEMENTATION_SUMMARY.md     # Technical details
├── requirements.txt              # Python dependencies
├── setup.py                      # Installation script
└── cfhelper/                     # Source code
    ├── __init__.py
    ├── config.py                 # Configuration management
    ├── utils.py                  # Utility functions
    ├── api.py                    # Codeforces API
    ├── scraper.py                # Test case scraping
    ├── start.py                  # start command
    ├── run.py                    # run command
    ├── addtest.py                # addtest command
    └── listen.py                 # ⭐ listen command (NEW)
```

## Commands Summary

| Command | Description | Documentation |
|---------|-------------|---------------|
| `cf contest listen` | ⭐ Listen for Competitive Companion | [COMPETITIVE_COMPANION_GUIDE.md](COMPETITIVE_COMPANION_GUIDE.md) |
| `start <contest-id>` | Setup contest structure | [README.md](README.md#setup-a-contest) |
| `addtest <problem>` | Add test cases | [WORKAROUNDS.md](WORKAROUNDS.md#solution-1-use-addtest-command-recommended) |
| `run <problem>` | Test solution | [README.md](README.md#test-a-solution) |

## Installation

See [README.md](README.md#installation) or [QUICKSTART.md](QUICKSTART.md#installation)

## Support

For issues or questions:
1. Check [WORKAROUNDS.md](WORKAROUNDS.md) for common problems
2. Review [QUICKSTART.md](QUICKSTART.md) for basic usage
3. Consult [README.md](README.md) for detailed documentation

## Version

CF Helper v1.0.0

## Last Updated

2026-02-11 - Added Competitive Companion integration
