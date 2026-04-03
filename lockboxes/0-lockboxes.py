#!/usr/bin/python3
"""Contains the canUnlockAll function"""


def canUnlockAll(boxes):
    """Determines if all the boxes can be opened.

    Args:
        boxes (list): A list of lists, where each sublist represents a box"""
    if not isinstance(boxes, list):
        return False
    if len(boxes) == 0:
        return True
    opened = set()
    queue = [0]
    opened.add(0)
    while queue:
        box = queue.pop(0)
        for key in boxes[box]:
            if key not in opened and key < len(boxes):
                opened.add(key)
                queue.append(key)
    return len(opened) == len(boxes)
