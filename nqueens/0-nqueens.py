#!/usr/bin/python3
"""
Solution au problème des N Reines (N Queens)
Utilise l'algorithme de backtracking pour trouver toutes les configurations
possibles de N reines non-attaquantes sur un échiquier N x N.
"""
import sys


def is_safe(board, row, col):
    """
    Vérifie si une reine peut être placée sur board[row][col].
    Comme on place une reine par ligne dans l'ordre croissant,
    on vérifie uniquement les lignes précédentes.
    """
    for i in range(row):
        # Vérification verticale (même colonne)
        if board[i] == col:
            return False
        # Vérification des diagonales
        if abs(board[i] - col) == abs(i - row):
            return False
    return True


def solve_nqueens(n, row, board, solutions):
    """
    Résout le problème de manière récursive avec backtracking.
    """
    if row == n:
        # Reconstitution du format de sortie [[row, col], ...]
        solution = [[i, board[i]] for i in range(n)]
        solutions.append(solution)
        return

    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col
            solve_nqueens(n, row + 1, board, solutions)


def main():
    """
    Gestion des arguments et point d'entrée principal.
    """
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    board = [-1] * n
    solutions = []
    solve_nqueens(n, 0, board, solutions)

    for solution in solutions:
        print(solution)


if __name__ == "__main__":
    main()
