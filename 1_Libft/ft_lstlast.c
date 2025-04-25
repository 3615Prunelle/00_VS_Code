/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/17 22:02:55 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The beginning of the list
Return : Last node of the list
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
// -------------------------------------------- Creating a ptr to the node I'll return (aka last one) ------------------------------------------ //
	t_list	*last;
	if (!lst)
		return(NULL);
// -------------------------------------------- Giving 'last' the same address as the head node, so it starts the loop at the right place ------ //
	last = lst;
// -------------------------------------------- Leaving the loop at the node before the last node ---------------------------------------------- //
	while (last->next != NULL)
	{
		last = last->next;
	}
// -------------------------------------------- When 'last.next' is NULL, means 'last' is the last node, so I return a pointer to it ----------- //
	return (last);
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
		printf("Node [%d]	Address [%p]	Content [%s]	Next [%p]\n", i, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		i++;
		loop_ptr = loop_ptr->next;
	}

	t_list *last_node = ft_lstlast(alix);
	printf ("\n⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅Pass in lstlast⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	printf("Last node address [%p] - Next (should be is null) %p - Content [%s]\n\n", last_node, last_node->next, (char *)last_node->content);
	free(alix);
	free(cleo);
	//free(mira);
	return(0);
} */
