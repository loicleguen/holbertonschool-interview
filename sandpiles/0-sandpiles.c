#include "sandpiles.h"
#include <stdio.h>

static int is_stable(int grid[3][3])
// Vérifie si la grille est stable (tous les éléments <= 3)
{
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] > 3)
				return (0);
	return (1);
}

static void print_grid(int grid[3][3])
// Affiche la grille au format demandé
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

void sandpiles_sum(int grid1[3][3], int grid2[3][3])
// Calcule la somme des deux grilles et stabilise le résultat
{
	int i, j;
	int copy[3][3];

	/* addition élément par élément */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			grid1[i][j] += grid2[i][j];

	/* tant que non stable, afficher et faire basculement simultané */
	while (!is_stable(grid1))
	{
		printf("=\n");
		print_grid(grid1);

		/* copie de l'état actuel pour traiter les topplings simultanés */
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				copy[i][j] = grid1[i][j];

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (copy[i][j] > 3)
				{
					grid1[i][j] -= 4;
					if (i - 1 >= 0)
						grid1[i - 1][j] += 1;
					if (i + 1 < 3)
						grid1[i + 1][j] += 1;
					if (j - 1 >= 0)
						grid1[i][j - 1] += 1;
					if (j + 1 < 3)
						grid1[i][j + 1] += 1;
				}
			}
		}
	}
}
