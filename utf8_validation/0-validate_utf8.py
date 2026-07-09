#!/usr/bin/python3
"""
Module for UTF-8 validation.
"""


def validUTF8(data):
    """
    Determines if a given data set represents a valid UTF-8 encoding.
    """
    # Nombre d'octets restants attendus pour le caractère actuel
    remaining_bytes = 0

    # Masques pour isoler les bits de poids fort
    mask1 = 1 << 7  # 10000000
    mask2 = 1 << 6  # 01000000

    for num in data:
        # On ne garde que les 8 bits les moins significatifs (1 octet)
        byte = num & 0xFF

        if remaining_bytes == 0:
            # On compte le nombre de 1 consécutifs au début du premier octet
            mask = 1 << 7
            while byte & mask:
                remaining_bytes += 1
                mask = mask >> 1

            # Caractère sur 1 octet (commence par 0)
            if remaining_bytes == 0:
                continue

            # UTF-8 valide uniquement pour 1 à 4 octets
            if remaining_bytes == 1 or remaining_bytes > 4:
                return False

            # On décrémente car on vient de traiter le premier octet
            remaining_bytes -= 1
        else:
            # C'est un octet de continuation : il doit commencer par '10'
            if not (byte & mask1 and not (byte & mask2)):
                return False
            remaining_bytes -= 1

    # Si la liste est finie mais qu'on attendait encore des octets
    return remaining_bytes == 0
