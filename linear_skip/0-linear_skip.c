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
	skiplist_t *node = list, *stop = NULL;

	if (list == NULL)
		return (NULL);

	/* Step 1: Traverse the express lane */
	while (node->express != NULL)
	{
		node = node->express;
		printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
		if (node->n >= value)
			break;
	}

	/* Step 2: Determine search range limits */
	if (node->n < value)
	{
		stop = node;
		while (stop->next != NULL)
			stop = stop->next;

		/* If we reached the end of express lane */
		/* node points to the last express node reached */
		/* The search range is between last express node and last list node */
		printf("Value found between indexes [%lu] and [%lu]\n",
		       node->index, stop->index);
	}
	else
	{
		/* Find previous express node or start at head */
		stop = node;
		node = list;
		while (node->express != stop && node->express != NULL)
			node = node->express;

		printf("Value found between indexes [%lu] and [%lu]\n",
		       node->index, stop->index);
	}

	/* Step 3: Linear search between node and stop */
	while (node != NULL && node->index <= stop->index)
	{
		printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
		if (node->n == value)
			return (node);
		node = node->next;
	}

	return (NULL);
}
