/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/21 13:53:29 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The t_list structure has been defined in .h - It can behave like a variable type.

The job of this function is just to store the void *content in the node.
No matter what type the content is, it’s meant to be generic.
That’s the whole point of using void * as the required argument */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*badass_node;

	if (!content)
		return (NULL);
// -------------------------------------------- Allocate memory for the new node = Will need to be free'd ------------------------------- //
	badass_node = malloc (sizeof(t_list));
	if (!badass_node)
		return (NULL);
// -------------------------------------------- Assign the content (any type bc 'content' was defined as void*) to the new node --------- //
	badass_node->content = content;
// -------------------------------------------- Set next to null (bc it's not connected to anything yet) -------------------------------- //
	badass_node->next = NULL;

	return (badass_node);
}

/* int	main(void)
{
	int	number = 42;

	t_list *head;				// I declare a pointer to the first node (head of the list) - defined in the t_list structure in .h
								// !!! Head is a pointer, not a node. So if there's a different node at the head, we have to make head point to it.
	head = ft_lstnew(&number);	//ft_lstnew wants a pointer(that stores an address) to anything (here : int)
	printf("Address of the fresh node :	[%p]\n", head);
// -------------------------------------------- Now, I need to cast the content back to an int pointer and dereference it ----------------- //
	printf("Content :			[%d]\n", *(int*)(head->content)); // Cast and dereference simultaneously, to print the int
	printf ("\n");
	free(head);
	return (0);
} */
