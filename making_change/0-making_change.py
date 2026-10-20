#!/usr/bin/python3
"""
Module pour le calcul du nombre minimum de pieces pour atteindre un total.
"""


def makeChange(coins, total):
    """
    Calcule le nombre minimum de pieces necessaires pour atteindre total.

    Args:
        coins (list): Liste des valeurs des pieces disponibles.
        total (int): Montant cible a atteindre.

    Returns:
        int: Nombre minimum de pieces, 0 si total <= 0, ou -1 si impossible.
    """
    if total <= 0:
        return 0

    # Tri décroissant des pièces
    coins.sort(reverse=True)

    count = 0
    for coin in coins:
        if total <= 0:
            break
        num_coins = total // coin
        count += num_coins
        total -= num_coins * coin

    if total != 0:
        return -1

    return count
