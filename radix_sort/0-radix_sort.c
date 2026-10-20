#include <stdlib.h>
#include "sort.h"

/**
 * get_max - recherche la valeur maximale dans un tableau d'entiers
 * @array: tableau d'entiers
 * @size: taille du tableau
 *
 * Return: la valeur maximale du tableau
 */
static int get_max(int *array, size_t size)
{
	int max;
	size_t i;

	max = array[0];
	for (i = 1; i < size; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	return (max);
}

/**
 * count_sort_lsd - trie selon le chiffre significatif passe en parametre
 * @array: tableau a trier
 * @size: taille du tableau
 * @exp: exposant representant la position du chiffre (1, 10, 100...)
 * @buffer: tableau temporaire pour stocker le resultat du tri
 */
static void count_sort_lsd(int *array, size_t size, int exp, int *buffer)
{
	int count[10] = {0};
	size_t i;

	/* Comptage des occurrences de chaque chiffre */
	for (i = 0; i < size; i++)
		count[(array[i] / exp) % 10]++;

	/* Cumul des positions */
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	/* Construction du tableau trie dans buffer */
    /* parcours inverse pour stabilite)*/
	for (i = size; i > 0; i--)
	{
		buffer[count[(array[i - 1] / exp) % 10] - 1] = array[i - 1];
		count[(array[i - 1] / exp) % 10]--;
	}

	/* Copie du buffer dans le tableau d'origine */
	for (i = 0; i < size; i++)
		array[i] = buffer[i];
}

/**
 * radix_sort - trie un tableau d'entiers avec l'algorithme Radix Sort (LSD)
 * @array: tableau d'entiers a trier
 * @size: taille du tableau
 */
void radix_sort(int *array, size_t size)
{
	int max, exp;
	int *buffer;

	if (array == NULL || size < 2)
		return;

	max = get_max(array, size);

	buffer = malloc(sizeof(int) * size);
	if (buffer == NULL)
		return;

	for (exp = 1; max / exp > 0; exp *= 10)
	{
		count_sort_lsd(array, size, exp, buffer);
		print_array(array, size);
	}

	free(buffer);
}
