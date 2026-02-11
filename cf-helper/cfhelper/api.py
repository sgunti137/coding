"""Codeforces API wrapper"""

import requests
from typing import Optional, List, Dict, Any


class CodeforcesAPI:
    """Wrapper for Codeforces API"""

    BASE_URL = "https://codeforces.com/api"

    @staticmethod
    def validate_contest(contest_id: int) -> bool:
        """Check if a contest exists"""
        try:
            url = f"{CodeforcesAPI.BASE_URL}/contest.standings"
            params = {
                'contestId': contest_id,
                'from': 1,
                'count': 1
            }
            response = requests.get(url, params=params, timeout=10)
            data = response.json()

            if data.get('status') == 'OK':
                return True
            return False
        except Exception as e:
            print(f"Error validating contest: {e}")
            return False

    @staticmethod
    def get_contest_problems(contest_id: int) -> Optional[List[str]]:
        """Get list of problem letters for a contest"""
        try:
            url = f"{CodeforcesAPI.BASE_URL}/contest.standings"
            params = {
                'contestId': contest_id,
                'from': 1,
                'count': 1
            }
            response = requests.get(url, params=params, timeout=10)
            data = response.json()

            if data.get('status') != 'OK':
                return None

            problems = data.get('result', {}).get('problems', [])
            # Extract problem indices (A, B, C, etc.)
            problem_letters = [p.get('index', '') for p in problems]
            # Filter out empty indices and sort
            problem_letters = [p for p in problem_letters if p]
            problem_letters.sort()

            return problem_letters
        except Exception as e:
            print(f"Error fetching problems: {e}")
            return None
