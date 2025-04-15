/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __________________BONUS____ft_lstnew.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/09 14:23:19 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
// The t_list structure has been defined in .h - It can behave like a variable type
t_list	*ft_lstnew(void *content)
/* The job of this function is just to store the void *content in the node.
No matter what type the content is, it’s meant to be generic.
That’s the whole point of using void * as the required argument */
{
	t_list *first_node;

	first_node = malloc (sizeof(t_list)); // Allocate memory for the new node
	if (!first_node)
		return (NULL);

	first_node->content = content; // Assign the content (any type bc "content" was defined as void*) in parameter to the new node
	first_node->next = NULL;  // Set next to null (bc it's the only node for now)

	return (first_node); // returns the newly created node
}

/* int	main(void)
{
	int	number = 42;

	t_list *head;				// I declare a pointer to the first node (head of the list) - defined in the t_list structure in .h
								// !!! Head is a pointer, not a node. So if there's a different node at the head, we have to make head point to it.
	head = ft_lstnew(&number);	//ft_lstnew wants a pointer(that stores an address) to anything (here : int)

	printf("Pointer to first node : %p\n", head);
	// Now, we need to cast the content back to an int pointer and dereference it
	printf("Data of first node : %d\n", *(int*)(head->content)); // Cast and dereference at the same time, to print the int

	free(head);

	return (0);
} */
