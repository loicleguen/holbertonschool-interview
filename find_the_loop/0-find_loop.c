#include "lists.h"

/**
 * find_listint_loop - trouve le debut de la boucle dans une liste chainee
 * @head: pointeur vers le premier noeud de la liste
 *
 * Return: l'adresse du noeud ou la boucle commence, ou NULL si pas de boucle
 */
listint_t *find_listint_loop(listint_t *head)
{
	listint_t *slow;
	listint_t *fast;

	if (head == NULL || head->next == NULL)
		return (NULL);

	slow = head;
	fast = head;

	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;

		/* Detection d'une boucle */
		if (slow == fast)
		{
			/* Reinitialisation de slow au debut pour trouver l'origine */
			slow = head;
			while (slow != fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
			return (slow);
		}
	}

	return (NULL);
}
