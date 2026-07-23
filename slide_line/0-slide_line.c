#include "slide_line.h"

/**
 * slide_left - Glisse et fusionne un tableau d'entiers vers la gauche
 * @line: Pointeur vers le tableau
 * @size: Nombre d'éléments dans le tableau
 */
static void slide_left(int *line, size_t size)
{
	size_t i, pos = 0;

	/* 1. Tasser vers la gauche */
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			if (pos != i)
			{
				line[pos] = line[i];
				line[i] = 0;
			}
			pos++;
		}
	}

	/* 2. Fusionner de gauche à droite */
	for (i = 0; i < size - 1; i++)
	{
		if (line[i] != 0 && line[i] == line[i + 1])
		{
			line[i] *= 2;
			line[i + 1] = 0;
			i++; /* Sauter l'élément suivant pour éviter la ré-fusion */
		}
	}

	/* 3. Tasser à nouveau après les fusions */
	pos = 0;
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			if (pos != i)
			{
				line[pos] = line[i];
				line[i] = 0;
			}
			pos++;
		}
	}
}

/**
 * slide_right - Glisse et fusionne un tableau d'entiers vers la droite
 * @line: Pointeur vers le tableau
 * @size: Nombre d'éléments dans le tableau
 */
static void slide_right(int *line, size_t size)
{
	size_t i, pos = size - 1;

	/* 1. Tasser vers la droite */
	for (i = size; i > 0; i--)
	{
		if (line[i - 1] != 0)
		{
			if (pos != i - 1)
			{
				line[pos] = line[i - 1];
				line[i - 1] = 0;
			}
			if (pos > 0)
				pos--;
		}
	}

	/* 2. Fusionner de droite à gauche de manière sécurisée */
	for (i = size - 1; i > 0; i--)
	{
		if (line[i] != 0 && line[i] == line[i - 1])
		{
			line[i] *= 2;
			line[i - 1] = 0;
			if (i == 1)
				break;
			i--; /* Sauter le précédent sans risquer l'underflow */
		}
	}

	/* 3. Tasser à nouveau après les fusions */
	pos = size - 1;
	for (i = size; i > 0; i--)
	{
		if (line[i - 1] != 0)
		{
			if (pos != i - 1)
			{
				line[pos] = line[i - 1];
				line[i - 1] = 0;
			}
			if (pos > 0)
				pos--;
		}
	}
}

/**
 * slide_line - Glisse et fusionne une ligne d'entiers dans une direction
 * @line: Pointeur vers le tableau d'entiers
 * @size: Nombre d'éléments dans le tableau
 * @direction: Direction du mouvement (SLIDE_LEFT ou SLIDE_RIGHT)
 *
 * Return: 1 en cas de succès, 0 en cas d'échec
 */
int slide_line(int *line, size_t size, int direction)
{
	if (!line || size == 0)
		return (0);

	if (direction == SLIDE_LEFT)
	{
		slide_left(line, size);
		return (1);
	}
	else if (direction == SLIDE_RIGHT)
	{
		slide_right(line, size);
		return (1);
	}

	return (0);
}
