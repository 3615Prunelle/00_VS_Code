/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_______BONUS_______.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/15 00:17:20 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	length;
	length = 0;

	t_list	*travelling_ptr;
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

	int length = ft_lstsize(alix); //alix is a pointer to the head, like requested in the function. No need to put &alix because that would be a pointer to a pointer
	printf("Length of the list : %d nodes\n", length);
	free(alix);
	free(cleo);
	free(mira);
	return(0);
} */
