/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_______BONUS_______.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/15 00:17:02 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
/*
lst: The beginning of the list
Return : Last node of the list
*/
	t_list	*last;				// Creating a ptr to the node I'll return (supposedly the last one)

	last = lst;					// Giving 'last' the same address as the head node, so it starts the loop at the right place
	while (last->next != NULL)	// Leaving the loop at the node before the last node
	{
		last = last->next;		// Jumping from a node to the next, in order
	}

	return (last);				// When 'last.next' is NULL, means 'last' is actually the last node, so I return a pointer to it
}
/* int	main(void)
{
	char *zucchine = "Zucchine";
	char *melanzane = "Melanzane";
	char *pomodori = "Pomodori";

	t_list *alix; // designating this pointer for the head
	t_list *cleo;
	t_list *mira;

	alix = ft_lstnew(zucchine);
	cleo = ft_lstnew(melanzane);
	mira = ft_lstnew(pomodori);

	ft_lstadd_front(&alix, cleo);
	ft_lstadd_front(&alix, mira);

	t_list *loop_ptr = alix;
	int i = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", i, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		i++;
		loop_ptr = loop_ptr->next;
	}

	t_list *last_node = ft_lstlast(alix);
	printf("\nLast node address [%p] - Check next is null [%p] - Content [%s]\n", last_node, last_node->next, (char *)last_node->content);
	free(alix);
	free(cleo);
	free(mira);
	return(0);
}
 */
