#include "push_swap.h"

t_node	*new_node(void *content)
{
	t_node	*node;

	if (!content)
		return (NULL);
	node = malloc (sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->index = 0;
	return (node);
}

t_node	*find_last_node(t_node *lst)
{
	t_node	*last;
	if (!lst)
		return(NULL);
	last = lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void		add_node_up(t_node **lst, t_node *new)
{
	if(!lst || !new)
		return;
	new->next = *lst;
	*lst = new;
}

void		add_node_down(t_node **lst, t_node *new)
{
	t_node *last;

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

int			count_nodes(t_node *lst)
{
	int		length;
	t_node	*travelling_ptr;

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
