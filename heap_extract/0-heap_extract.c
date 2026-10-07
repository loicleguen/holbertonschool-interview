#include <stdlib.h>
#include "binary_trees.h"

/**
 * tree_size - Measures the size of a binary tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: Size of the tree, or 0 if tree is NULL
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * get_last_node - Finds the last node in level-order using bitwise pathing
 * @root: Pointer to the root node of the tree
 * @size: Total number of nodes in the tree
 *
 * Return: Pointer to the last node
 */
static heap_t *get_last_node(heap_t *root, size_t size)
{
	int bit;
	heap_t *node = root;

	for (bit = 0; (size >> bit) > 1; bit++)
		;

	for (bit--; bit >= 0; bit--)
	{
		if ((size >> bit) & 1)
			node = node->right;
		else
			node = node->left;
	}

	return (node);
}

/**
 * heapify_down - Restores the Max Heap property from root downwards
 * @root: Pointer to the root node of the heap
 */
static void heapify_down(heap_t *root)
{
	heap_t *curr = root, *max_child;
	int temp;

	while (curr->left)
	{
		max_child = curr->left;
		if (curr->right && curr->right->n > curr->left->n)
			max_child = curr->right;

		if (curr->n >= max_child->n)
			break;

		temp = curr->n;
		curr->n = max_child->n;
		max_child->n = temp;

		curr = max_child;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	int value;
	size_t size;
	heap_t *last_node;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	size = tree_size(*root);

	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	last_node = get_last_node(*root, size);

	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}

	(*root)->n = last_node->n;
	free(last_node);

	heapify_down(*root);

	return (value);
}
