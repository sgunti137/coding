"""Configuration management for CF Helper"""

import os
import yaml
from pathlib import Path
from typing import Dict, Any, Optional

CONFIG_DIR = Path.home() / '.cfhelper'
CONFIG_FILE = CONFIG_DIR / 'config.yaml'

DEFAULT_CONFIG = {
    'template_path': '',
    'base_dir': '',
    'compiler': 'g++',
    'compile_flags': ['-std=c++17', '-O2', '-Wall'],
    'active_contest': None,
    'timeout': 2.0,
}


def ensure_config_dir():
    """Create config directory if it doesn't exist"""
    CONFIG_DIR.mkdir(parents=True, exist_ok=True)


def load_config() -> Dict[str, Any]:
    """Load configuration from file or return default"""
    if not CONFIG_FILE.exists():
        return DEFAULT_CONFIG.copy()

    try:
        with open(CONFIG_FILE, 'r') as f:
            config = yaml.safe_load(f)
            # Merge with defaults to handle missing keys
            result = DEFAULT_CONFIG.copy()
            if config:
                result.update(config)
            return result
    except Exception as e:
        print(f"Error loading config: {e}")
        return DEFAULT_CONFIG.copy()


def save_config(config: Dict[str, Any]):
    """Save configuration to file"""
    ensure_config_dir()
    try:
        with open(CONFIG_FILE, 'w') as f:
            yaml.dump(config, f, default_flow_style=False)
    except Exception as e:
        print(f"Error saving config: {e}")


def get_config_value(key: str) -> Any:
    """Get a specific config value"""
    config = load_config()
    return config.get(key)


def set_config_value(key: str, value: Any):
    """Set a specific config value"""
    config = load_config()
    config[key] = value
    save_config(config)


def is_first_run() -> bool:
    """Check if this is the first time running the tool"""
    config = load_config()
    return not config.get('template_path') or not config.get('base_dir')


def prompt_first_time_setup():
    """Interactive first-time setup"""
    print("First time setup for CF Helper")
    print("-" * 40)

    # Prompt for template path
    default_template = '/mnt/c/Users/saakethgunti/Development Work/coding/Contests/template.cpp'
    template_path = input(f"Template C++ file path [{default_template}]: ").strip()
    if not template_path:
        template_path = default_template

    # Verify template exists
    if not os.path.exists(template_path):
        print(f"Warning: Template file not found at {template_path}")
        create_anyway = input("Continue anyway? (y/n): ").strip().lower()
        if create_anyway != 'y':
            print("Setup cancelled.")
            exit(1)

    # Prompt for base directory
    default_base = '/mnt/c/Users/saakethgunti/Development Work/coding/Contests'
    base_dir = input(f"Contests base directory [{default_base}]: ").strip()
    if not base_dir:
        base_dir = default_base

    # Verify base directory exists
    if not os.path.exists(base_dir):
        print(f"Warning: Base directory not found at {base_dir}")
        create_dir = input("Create it? (y/n): ").strip().lower()
        if create_dir == 'y':
            os.makedirs(base_dir, exist_ok=True)
        else:
            print("Setup cancelled.")
            exit(1)

    # Save configuration
    config = load_config()
    config['template_path'] = template_path
    config['base_dir'] = base_dir
    save_config(config)

    print("\nConfiguration saved!")
    print(f"Template: {template_path}")
    print(f"Base directory: {base_dir}")
    print("-" * 40)
