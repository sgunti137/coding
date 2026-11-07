"""Per-site settings shared by the Competitive Companion listeners (Codeforces, AtCoder)."""

import json
import re
from pathlib import Path

from .config import load_config


class Codeforces:
    name = 'Codeforces'
    command = 'cf'

    @staticmethod
    def parse(url):
        """URL -> (contest_id, letter, task_id) or None."""
        m = (re.search(r'/contest/(\d+)/problem/([A-Z]\d*)', url)
             or re.search(r'/problemset/problem/(\d+)/([A-Z]\d*)', url))
        return (m.group(1), m.group(2), None) if m else None

    @staticmethod
    def root(config):
        return Path(config['base_dir'])

    @staticmethod
    def template(config):
        return config['template_path']

    @classmethod
    def problem_dir(cls, config, contest_id, letter, single):
        root = cls.root(config)
        return root / f'{contest_id}{letter}' if single else root / contest_id / letter

    @staticmethod
    def save_meta(folder, contest_id, task_id, url):
        pass


class AtCoder:
    name = 'AtCoder'
    command = 'ac'

    @staticmethod
    def parse(url):
        m = re.search(r'atcoder\.jp/contests/([^/]+)/tasks/([^/?#]+)', url)
        if not m:
            return None
        task_id = m.group(2)
        return m.group(1), task_id.rsplit('_', 1)[-1].upper(), task_id

    @staticmethod
    def root(config):
        if config.get('atcoder_dir'):
            return Path(config['atcoder_dir'])
        return Path(config['base_dir']).parent / 'Atcoder'

    @staticmethod
    def template(config):
        return config.get('atcoder_template_path') or config['template_path']

    @classmethod
    def problem_dir(cls, config, contest_id, letter, single):
        # Single problems also go in <contest>/<letter> so `ac submit` can find them the same way
        return cls.root(config) / contest_id / letter

    @staticmethod
    def save_meta(folder, contest_id, task_id, url):
        (folder / '.ac.json').write_text(json.dumps(
            {'contest': contest_id, 'task_id': task_id, 'url': url}, indent=2))


def config_for(site):
    config = load_config()
    site.root(config).mkdir(parents=True, exist_ok=True)
    return config
