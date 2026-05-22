#!/usr/bin/python3
"""
Module pour parser des logs en temps réel depuis stdin.
Affiche les statistiques toutes les 10 lignes ou lors d'un Ctrl+C.
"""
import sys


def print_stats(total_size, status_codes):
    """
    Affiche les statistiques au format demandé.
    """
    print("File size: {}".format(total_size))
    for code in sorted(status_codes.keys()):
        if status_codes[code] > 0:
            print("{}: {}".format(code, status_codes[code]))


def parse_logs():
    """
    Lit stdin ligne par ligne et traite les données.
    """
    total_size = 0
    # Liste des codes autorisés initialisés à 0
    status_codes = {
        "200": 0, "301": 0, "400": 0, "401": 0,
        "403": 0, "404": 0, "405": 0, "500": 0
    }
    line_count = 0

    try:
        for line in sys.stdin:
            line_count += 1
            # Séparer la ligne par les espaces depuis la fin
            # Format attendu : ... "GET /projects/260 HTTP/1.1" <status> <size>
            parts = line.split()

            # On vérifie qu'on a assez d'éléments pour extraire code et taille
            if len(parts) >= 2:
                # La taille est le dernier élément, le code est l'avant-dernier
                status = parts[-2]
                size = parts[-1]

                # Accumulation de la taille si c'est un entier valide
                try:
                    total_size += int(size)
                except ValueError:
                    pass

                # Incrémentation du code de statut s'il fait partie de la liste
                if status in status_codes:
                    status_codes[status] += 1

            # Affichage toutes les 10 lignes
            if line_count % 10 == 0:
                print_stats(total_size, status_codes)

        # Si le flux stdin se termine proprement sans interruption
        print_stats(total_size, status_codes)

    except KeyboardInterrupt:
        # Gestion du Ctrl + C : on affiche les stats
        # courantes puis on lève à nouveau l'exception
        print_stats(total_size, status_codes)
        raise


if __name__ == "__main__":
    parse_logs()
