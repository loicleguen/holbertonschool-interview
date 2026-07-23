#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * is_hole - Vérifie si une coordonnée (row, col) est un trou
 * @row: Ligne dans la grille
 * @col: Colonne dans la grille
 *
 * Return: 1 si c'est un trou (espace), 0 sinon (#)
 */
static int is_hole(int row, int col)
{
	while (row > 0 || col > 0)
	{
		if (row % 3 == 1 && col % 3 == 1)
			return (1);
		row /= 3;
		col /= 3;
	}
	return (0);
}

/**
 * menger - Dessine une éponge de Menger en 2D pour un niveau donné
 * @level: Niveau de l'éponge de Menger
 */
void menger(int level)
{
	int size, row, col;

	if (level < 0)
		return;

	size = (int)pow(3, level);

	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			if (is_hole(row, col))
				printf(" ");
			else
				printf("#");
		}
		printf("\n");
	}
}
