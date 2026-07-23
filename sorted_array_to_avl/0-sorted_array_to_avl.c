#include "binary_trees.h"

/**
 * create_node - Crée un nouveau nœud d'arbre binaire
 * @parent: Pointeur vers le nœud parent
 * @value: Valeur à stocker dans le nouveau nœud
 *
 * Return: Pointeur vers le nouveau nœud, ou NULL en cas d'échec
 */
static avl_t *create_node(avl_t *parent, int value)
{
	avl_t *new_node;

	new_node = malloc(sizeof(avl_t));
	if (!new_node)
		return (NULL);

	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

/**
 * build_avl - Construit récursivement un
 * arbre AVL à partir d'un tableau trié
 * @array: Pointeur vers le premier élément du sous-tableau
 * @start: Indice de début du sous-tableau
 * @end: Indice de fin du sous-tableau
 * @parent: Pointeur vers le nœud parent
 *
 * Return: Pointeur vers le nœud racine créé, ou NULL en cas d'échec
 */
static avl_t *build_avl(int *array, size_t start, size_t end, avl_t *parent)
{
	size_t mid;
	avl_t *root;

	if (start > end)
		return (NULL);

	mid = (start + end) / 2;

	root = create_node(parent, array[mid]);
	if (!root)
		return (NULL);

	if (mid > start)
		root->left = build_avl(array, start, mid - 1, root);

	if (mid < end)
		root->right = build_avl(array, mid + 1, end, root);

	return (root);
}

/**
 * sorted_array_to_avl - Construit un arbre AVL à partir d'un tableau trié
 * @array: Pointeur vers le premier élément du tableau à convertir
 * @size: Nombre d'éléments dans le tableau
 *
 * Return: Pointeur vers la racine de l'arbre
 * AVL créé, ou NULL en cas d'échec
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);

	return (build_avl(array, 0, size - 1, NULL));
}
