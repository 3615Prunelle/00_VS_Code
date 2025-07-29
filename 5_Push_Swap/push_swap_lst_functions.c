#include "push_swap.h"

linked_node	*new_node(void *content)
{
	linked_node	*node;

	if (!content)
		return (NULL);
	node = malloc (sizeof(linked_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->index = 0;
	return (node);
}

linked_node	*find_last_node(linked_node *lst)
{
	linked_node	*last;
	if (!lst)
		return(NULL);
	last = lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void		add_node_up(linked_node **lst, linked_node *new)
{
	if(!lst || !new)
		return;
	new->next = *lst;
	*lst = new;
}

void		add_node_down(linked_node **lst, linked_node *new)
{
	linked_node *last;

	if (!lst || !new)
		return;
	if (!*lst)
	{
		*lst = new;
		//new->next = NULL; // NOPE, because 'new' may not be the last node
		return;
	}
	last = find_last_node(*lst);
	last->next = new;
	//new->next = NULL; // NOPE, because 'new' may not be the last node
}

int			count_nodes(linked_node *lst)
{
	int		length;
	linked_node	*travelling_ptr;

	if (!lst)
		return (0);
	length = 0;
	travelling_ptr = lst;
	while (travelling_ptr != NULL)
	{
		travelling_ptr = travelling_ptr->next;
		length++;
	}
	return (length);
}
