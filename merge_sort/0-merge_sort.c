#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * merge - fusionne deux sous-tableaux tries dans le tableau principal
 * @array: tableau d'origine
 * @buffer: tableau temporaire pour la fusion
 * @left: pointeur vers le sous-tableau gauche
 * @left_size: taille du sous-tableau gauche
 * @right: pointeur vers le sous-tableau droit
 * @right_size: taille du sous-tableau droit
 */
static void merge(int *array, int *buffer, int *left, size_t left_size,
		  int *right, size_t right_size)
{
	size_t i = 0, j = 0, k = 0;

	printf("Merging...\n");
	printf("[left]: ");
	print_array(left, left_size);
	printf("[right]: ");
	print_array(right, right_size);

	/* Fusion des deux sous-tableaux dans le buffer */
	while (i < left_size && j < right_size)
	{
		if (left[i] <= right[j])
			buffer[k++] = left[i++];
		else
			buffer[k++] = right[j++];
	}

	while (i < left_size)
		buffer[k++] = left[i++];

	while (j < right_size)
		buffer[k++] = right[j++];

	/* Copie des elements fusionnes du buffer vers le tableau d'origine */
	for (i = 0; i < left_size + right_size; i++)
		array[i] = buffer[i];

	printf("[Done]: ");
	print_array(array, left_size + right_size);
}

/**
 * merge_sort_recursive - divise le tableau et appelle la fusion
 * @array: tableau a trier
 * @buffer: tableau temporaire partage pour éviter les malloc multiples
 * @size: taille du tableau courant
 */
static void merge_sort_recursive(int *array, int *buffer, size_t size)
{
	size_t mid;
	int *left;
	int *right;
	size_t right_size;

	if (size < 2)
		return;

	mid = size / 2;
	left = array;
	right = array + mid;
	right_size = size - mid;

	/* Tri du sous-tableau gauche puis du sous-tableau droit */
	merge_sort_recursive(left, buffer, mid);
	merge_sort_recursive(right, buffer, right_size);

	/* Fusion des deux sous-tableaux */
	merge(array, buffer, left, mid, right, right_size);
}

/**
 * merge_sort - trie un tableau d'entiers en utilisant le tri par fusion
 * @array: tableau d'entiers a trier
 * @size: nombre d'elements dans le tableau
 */
void merge_sort(int *array, size_t size)
{
	int *buffer;

	if (array == NULL || size < 2)
		return;

	/* Un seul appel a malloc pour l'ensemble du processus de tri */
	buffer = malloc(sizeof(int) * size);
	if (buffer == NULL)
		return;

	merge_sort_recursive(array, buffer, size);

	free(buffer);
}
