/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:45:39 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

my_first_linked_list	*ft_lstnew (void *data)
{
	my_first_linked_list *first_node;

	first_node = malloc (sizeof(my_first_linked_list)); // Allocate memory for the new node

	if (!first_node)
		return (NULL);

	first_node -> data = data; // Assign the content in parameter to the new node
	first_node -> next = NULL; // Set next to null (bc it's the only node for now)

	return (first_node);
}

int	main(void)
{
	char	number = 42;

	my_first_linked_list *node_1 = (char) ft_lstnew (&number);

	if (!node_1)
	{
		printf ("Fail");
		return (0);
	}
	printf ("Something is going on\n");

	char another_number = 100;
	my_first_linked_list *node_2 = ft_lstnew (&another_number);

	if (!node_2)
	{
		printf ("Fail");
		return (0);
	}

	printf ("Node 1 : %p devient %c\n", (void *)node_1, *(char *)node_1 -> data);
	printf ("Node 2 : %p devient %c\n", (void *)node_2, *(char *)node_2 -> data);

	free (node_1);
	free (node_2);

	return (0);
}
