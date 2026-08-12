#!/usr/bin/python3
"""
Module 0-rain

Contains the function rain to calculate retained rainwater between walls.
"""


def rain(walls):
    """
    Calculate how many square units of water will be retained after it rains.

    Args:
        walls (list): List of non-negative integers representing wall heights.

    Returns:
        int: Total amount of rainwater retained.
    """
    if not walls or not isinstance(walls, list):
        return 0

    left = 0
    right = len(walls) - 1
    left_max = 0
    right_max = 0
    total_water = 0

    while left < right:
        if walls[left] < walls[right]:
            if walls[left] >= left_max:
                left_max = walls[left]
            else:
                total_water += left_max - walls[left]
            left += 1
        else:
            if walls[right] >= right_max:
                right_max = walls[right]
            else:
                total_water += right_max - walls[right]
            right -= 1

    return total_water
