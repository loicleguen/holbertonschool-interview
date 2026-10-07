#!/usr/bin/python3
"""
Module pour la rotation d'une matrice 2D n x n.
"""


def rotate_2d_matrix(matrix):
    """
    Tourne une matrice 2D n x n de 90 degres dans le sens horaire sur place.

    Args:
        matrix (list of list of int): La matrice a modifier.
    """
    n = len(matrix)

    # 1. Transposer la matrice
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

    # 2. Inverser chaque ligne
    for i in range(n):
        matrix[i].reverse()
