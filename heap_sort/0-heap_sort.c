#include "sort.h"

/**
 * swap_ints - Swaps two integers in an array and prints the array.
 * @array: The array containing the integers.
 * @size: Total size of the array for printing.
 * @a: Pointer to first integer.
 * @b: Pointer to second integer.
 */
void swap_ints(int *array, size_t size, int *a, int *b)
{
	if (*a != *b)
	{
		*a = *a ^ *b;
		*b = *a ^ *b;
		*a = *a ^ *b;
		print_array(array, size);
	}
}

/**
 * sift_down - Sifts down a node to maintain the max-heap property.
 * @array: The array representing the heap.
 * @size: Total size of the array (for printing).
 * @heap_size: Current size of the active heap.
 * @root: Index of the root of the subtree to sift down.
 */
void sift_down(int *array, size_t size, size_t heap_size, size_t root)
{
	size_t largest = root;
	size_t left = 2 * root + 1;
	size_t right = 2 * root + 2;

	if (left < heap_size && array[left] > array[largest])
		largest = left;

	if (right < heap_size && array[right] > array[largest])
		largest = right;

	if (largest != root)
	{
		swap_ints(array, size, &array[root], &array[largest]);
		sift_down(array, size, heap_size, largest);
	}
}

/**
 * heap_sort - Sorts an array of integers in ascending order
 *             using the Heap sort algorithm (sift-down).
 * @array: The array of integers to sort.
 * @size: Size of the array.
 */
void heap_sort(int *array, size_t size)
{
	int i;

	if (!array || size < 2)
		return;

	/* 1. Build Max Heap (bottom-up using sift-down) */
	for (i = (size / 2) - 1; i >= 0; i--)
		sift_down(array, size, size, i);

	/* 2. Extract elements from the heap one by one */
	for (i = size - 1; i > 0; i--)
	{
		swap_ints(array, size, &array[0], &array[i]);
		sift_down(array, size, i, 0);
	}
}
