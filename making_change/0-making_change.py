#!/usr/bin/python3
"""
Module pour déterminer le nombre minimum de pièces requis.
"""


def makeChange(coins, total):
    """
    Calcule le nombre minimum de pieces necessaires pour atteindre total.

    Args:
        coins (list): Liste des valeurs des pièces à disposition.
        total (int): Somme totale à atteindre.

    Returns:
        int: Nombre minimum de pièces nécessaires, 0 si total <= 0,
             ou -1 si le total ne peut pas être atteint.
    """
    if total <= 0:
        return 0

    # Tableau DP initialisé avec une valeur impossible (total + 1)
    dp = [total + 1] * (total + 1)
    dp[0] = 0

    for i in range(1, total + 1):
        for coin in coins:
            if i - coin >= 0:
                dp[i] = min(dp[i], dp[i - coin] + 1)

    return dp[total] if dp[total] != total + 1 else -1
