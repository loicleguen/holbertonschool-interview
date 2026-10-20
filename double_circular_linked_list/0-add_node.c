#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * create_node - cree un nouveau noeud pour la liste circulaire
 * @str: chaine a copier dans le nouveau noeud
 *
 * Return: pointeur vers le nouveau noeud, ou NULL en cas d'echec
 */
static List *create_node(char *str)
{
	List *new_node;

	if (str == NULL)
		return (NULL);

	new_node = malloc(sizeof(List));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;
	new_node->prev = NULL;

	return (new_node);
}

/**
 * add_node_end - ajoute un nouveau noeud a la fin
 *                d'une liste circulaire double
 * @list: pointeur vers le pointeur de la tete de liste
 * @str: chaine a copier dans le nouveau noeud
 *
 * Return: adresse du nouveau noeud, ou NULL en cas d'echec
 */
List *add_node_end(List **list, char *str)
{
	List *new_node, *last;

	if (list == NULL)
		return (NULL);

	new_node = create_node(str);
	if (new_node == NULL)
		return (NULL);

	if (*list == NULL)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		*list = new_node;
		return (new_node);
	}

	last = (*list)->prev;

	new_node->next = *list;
	new_node->prev = last;
	last->next = new_node;
	(*list)->prev = new_node;

	return (new_node);
}

/**
 * add_node_begin - ajoute un nouveau noeud au debut
 *                  d'une liste circulaire double
 * @list: pointeur vers le pointeur de la tete de liste
 * @str: chaine a copier dans le nouveau noeud
 *
 * Return: adresse du nouveau noeud, ou NULL en cas d'echec
 */
List *add_node_begin(List **list, char *str)
{
	List *new_node;

	new_node = add_node_end(list, str);
	if (new_node == NULL)
		return (NULL);

	*list = new_node;
	return (new_node);
}
