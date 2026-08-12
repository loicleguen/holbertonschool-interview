#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list of integers.
 * @list: Pointer to the head of the skip list to search in.
 * @value: The value to search for.
 *
 * Return: Pointer to the first node where value is located, or NULL if absent.
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *node = list, *express = NULL;

	if (!list)
		return (NULL);

	while (node->express)
	{
		express = node->express;
		printf("Value checked at index [%lu] = [%d]\n", express->index, express->n);
		if (express->n >= value)
			break;
		node = express;
	}

	if (express && express->n >= value)
		printf("Value found between indexes [%lu] and [%lu]\n",
		       node->index, express->index);
	else
	{
		node = express ? express : list;
		express = node;
		while (express->next)
			express = express->next;
		printf("Value found between indexes [%lu] and [%lu]\n",
		       node->index, express->index);
	}

	while (node)
	{
		printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
		if (node->n == value)
			return (node);
		if (node == express)
			break;
		node = node->next;
	}

	return (NULL);
}
