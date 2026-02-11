"""Setup script for CF Helper"""

from setuptools import setup, find_packages

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

setup(
    name='cf-helper',
    version='1.0.0',
    description='Codeforces Contest Setup and Testing Tool',
    author='Saaketh Gunti',
    packages=find_packages(),
    install_requires=requirements,
    entry_points={
        'console_scripts': [
            # Main commands
            'cf=cfhelper.cli:cli',
            'start=cfhelper.start:main',
            'run=cfhelper.run:main',
            'addtest=cfhelper.addtest:main',
        ],
    },
    python_requires='>=3.7',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
    ],
)
