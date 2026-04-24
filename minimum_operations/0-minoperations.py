#!/usr/bin/python3
"""Minimum Operations"""


def minOperations(n):
    """Returns the minimum number of operations needed
    to result in exactly n H characters in the file."""
    if n <= 1:
        return 0

    operations = 0
    current_length = 1
    clipboard = 0

    while current_length < n:
        if n % current_length == 0:
            clipboard = current_length
            operations += 1  # Copy All
        current_length += clipboard
        operations += 1  # Paste

    return operations
