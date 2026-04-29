#include <stdlib.h>
#include "lists.h"

/**
 * list_len - Get the length of a linked list
 * @head: Pointer to the head of the list
 *
 * Return: The number of nodes
 */
static size_t list_len(const listint_t *head)
{
	size_t len = 0;

	while (head != NULL)
	{
		len++;
		head = head->next;
	}

	return (len);
}

/**
 * reverse_list - Reverse a singly linked list
 * @head: Pointer to the head of the list
 *
 * Return: Pointer to the new head of the reversed list
 */
static listint_t *reverse_list(listint_t *head)
{
	listint_t *prev = NULL;
	listint_t *next = NULL;

	while (head != NULL)
	{
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	return (prev);
}

/**
 * is_palindrome - Check if a singly linked list is a palindrome
 * @head: Double pointer to the head of the list
 *
 * Return: 1 if the list is a palindrome, 0 otherwise
 */
int is_palindrome(listint_t **head)
{
	listint_t *first;
	listint_t *second;
	listint_t *copy;
	size_t len;
	size_t i;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return (1);

	len = list_len(*head);
	first = *head;

	for (i = 0; i < len / 2; i++)
		first = first->next;

	if (len % 2 != 0)
		first = first->next;

	second = reverse_list(first);
	copy = second;
	first = *head;

	for (i = 0; i < len / 2; i++)
	{
		if (first->n != second->n)
		{
			reverse_list(copy);
			return (0);
		}
		first = first->next;
		second = second->next;
	}

	reverse_list(copy);
	return (1);
}
