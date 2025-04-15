/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_______BONUS_______.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/15 00:15:43 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
/*
lst: The address of a pointer to the first node of a list.
new: The address of a pointer to the node to be added.
Return : None
Adds the node ’new’ at the end of the list.
*/
	t_list *last;				// creating a pointer to find the last node of the list
	last = ft_lstlast(*lst);	// accessing to that node and getting its address

	last->next = new;
	new->next = NULL;

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

	t_list *isidor;
	isidor = ft_lstnew("It's the final countdown");
	ft_lstadd_back(&alix, isidor);

	t_list *loop_ptr = alix;
	int node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
	free(alix);
	free(cleo);
	free(mira);
	free(isidor);
	return(0);
}

 */
