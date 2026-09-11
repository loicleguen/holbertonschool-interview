#include "search_algos.h"

/**
 * advanced_binary - Recherche la première occurrence d'une valeur
 *                   dans un tableau trié en utilisant la récursion.
 * @array: Pointeur vers le premier élément du tableau.
 * @size: Nombre d'éléments dans le tableau.
 * @value: Valeur à rechercher.
 *
 * Return: L'indice où la valeur se trouve, ou -1 si absente.
 */

int advanced_binary(int *array, size_t size, int value)
{
	size_t i, mid;
	int result;

	if (array == NULL || size == 0)
	return (-1);

	printf("Searching in array: ");
	for (i = 0; i < size; i++)
	{
		printf("%d", array[i]);
		if (i < size - 1)
			printf(", ");
	}
	printf("\n");

	mid = (size - 1) / 2;

	if (array[mid] == value && mid == 0)
		return ((int)mid);

	if (array[mid] >= value)
		return (advanced_binary(array, mid + 1, value));

	result = advanced_binary(array + mid + 1, size - (mid + 1), value);
	if (result == -1)
		return (-1);

	return ((int)(mid + 1 + result));
}
