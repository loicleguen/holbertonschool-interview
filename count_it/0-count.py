#!/usr/bin/python3
"""
Module pour compter de façon récursive les mots-clés dans les titres
des articles "hot" d'un subreddit via l'API Reddit.
"""
import requests


def count_words(subreddit, word_list, after=None, word_counts=None):
    """
    Interroge récursivement l'API Reddit, analyse les titres des articles
    "hot" et affiche un décompte trié des mots-clés fournis.
    """
    if word_counts is None:
        # Nettoyage et normalisation de la liste des mots-clés en minuscules
        word_counts = {}
        for word in word_list:
            w = word.lower()
            if w not in word_counts:
                word_counts[w] = 0

    url = "https://www.reddit.com/r/{}/hot.json".format(subreddit)
    headers = {'User-Agent': 'CustomUserAgent/1.0'}
    params = {'after': after, 'limit': 100}

    try:
        response = requests.get(url, headers=headers, params=params,
                                allow_redirects=False)
        if response.status_code != 200:
            return
    except Exception:
        return

    data = response.json().get('data', {})
    children = data.get('children', [])

    # Traitement des titres de la page courante
    for child in children:
        title = child.get('data', {}).get('title', '')
        # Séparation stricte par les espaces pour exclure java. ou java!
        words_in_title = [w.lower() for w in title.split()]
        for word in words_in_title:
            if word in word_counts:
                word_counts[word] += 1

    next_after = data.get('after')

    # Appel récursif s'il reste des pages
    if next_after is not None:
        return count_words(subreddit, word_list, next_after, word_counts)

    # Une fois la récursion terminée (plus de page suivante), on filtre et trie
    filtered_counts = {k: v for k, v in word_counts.items() if v > 0}
    if not filtered_counts:
        return

    # Si le mot-clé d'origine contenait des doublons (ex: 'java JAvA'),
    # on applique le multiplicateur correspondant
    raw_words_lower = [w.lower() for w in word_list]
    multipliers = {}
    for w in raw_words_lower:
        multipliers[w] = multipliers.get(w, 0) + 1

    final_results = {}
    for word, count in filtered_counts.items():
        final_results[word] = count * multipliers[word]

    # Tri : ordre décroissant par le décompte (-val[1]),
    # puis ordre alphabétique croissant par le mot (val[0])
    sorted_words = sorted(
        final_results.items(), key=lambda val: (-val[1], val[0]))

    for word, count in sorted_words:
        print("{}: {}".format(word, count))
