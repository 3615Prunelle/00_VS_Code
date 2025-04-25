/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/21 13:53:01 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		length;
	t_list	*travelling_ptr;

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
/* int	main(void)
{
	char *zucchine = ft_strdup("Zucchine");	// FREE : at the end of main
	char *melanzane = ft_strdup("Melanzane");
	char *pomodori = ft_strdup("Pomodori");

	t_list *alix;					// designating this pointer for the head
	t_list *cleo;
	t_list *mira;

	alix = ft_lstnew(zucchine);		// FREE : at the end of main
	cleo = ft_lstnew(melanzane);
	mira = ft_lstnew(pomodori);

	ft_lstadd_front(&alix, cleo);
	ft_lstadd_front(&alix, mira);	// mira becomes the first node

	t_list *loop_ptr = alix;
	int i = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", i, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		i++;
		loop_ptr = loop_ptr->next;
	}

	printf ("\n⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅Pass in lstsize⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	int length = ft_lstsize(alix);	//alix is a pointer to the head, like requested as the function parameter. No need to put &alix because that would be a pointer to a pointer
	printf("Length of the list : %d nodes\n", length);
	ft_lstclear(&alix, del);		// always use this function when more than one node to free, otherwise double free issues - attention, ne marche pas si content n'a pas ete malloc'd
	return(0);
} */
