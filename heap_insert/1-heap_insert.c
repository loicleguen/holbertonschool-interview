#include "binary_trees.h"
#include <stdlib.h>

/**
 * swap_values - Swap the values of two nodes
 * @a: first node
 * @b: second node
 */
void swap_values(heap_t *a, heap_t *b)
{
	int tmp = a->n;

	a->n = b->n;
	b->n = tmp;
}

/**
 * heapify_up - Move the node up to maintain heap property
 * @node: pointer to the node to heapify
 */
void heapify_up(heap_t *node)
{
	while (node->parent && node->n > node->parent->n)
	{
		swap_values(node, node->parent);
		node = node->parent;
	}
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: double pointer to the root node
 * @value: value to insert
 * Return: pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	heap_t **queue;
	size_t front = 0, rear = 0, size = 0;

	if (!root)
		return (NULL);

	if (!*root)
		return (*root = binary_tree_node(NULL, value));

	/* BFS to find the first available spot */
	size = 1024; /* Large enough for most cases */
	queue = malloc(sizeof(heap_t *) * size);
	if (!queue)
		return (NULL);
	queue[rear++] = *root;

	while (front < rear)
	{
		parent = queue[front++];
		if (!parent->left || !parent->right)
			break;
		queue[rear++] = parent->left;
		queue[rear++] = parent->right;
	}
	free(queue);

	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);
	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	heapify_up(new_node);

	return (new_node);
}
