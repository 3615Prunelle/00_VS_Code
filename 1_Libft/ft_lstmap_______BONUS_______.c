/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_______BONUS_______.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/15 00:17:08 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
/*
lst: The address of a pointer to a node.
f: The address of the function applied to each node’s content.
del: The address of the function used to delete a node’s content if needed.
Return : The new list. NULL if the allocation fails.
Use : Malloc / Free
Iterates through the list ’lst’, applies the function ’f’ to each node’s content, and creates
a new list resulting of the successive applications of the function ’f’.
The ’del’ function is used to delete the content of a node if needed.
*/

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
	return(0);
}
 */
