/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_______BONUS_______.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/15 19:43:10 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *);

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{

/* Step 1 : Fetch the data to erase (using 'node.content') - In this case, it would be ```lst->content``` because lst is a pointer, so I use the -> */
/* Step 2 : Call the del function, giving the data to erase (Step 1) as a parameter.
!!! Make sure I'm not trying to free something that wasn't dynamically allocated (crash). Check if a malloc has been done on the actual content (not just the pointer)
*/

del(lst->content);

/*Step 4 : Free the pointer to the node, as it's been malloc'd in ft_lstnew*/
free(lst);
lst = NULL; // to avoid dangling pointer

}

/* Step 3 : Create the del function, that takes any kind of data as a parameter, and frees this data - free(void*) not ok. Instead, name the parameter and call free() on it.*/
void	del(void *param)
{
	free(param);
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

	ft_lstadd_back(&alix, cleo);
	ft_lstadd_back(&alix, mira);

// ---------------------------- Adding a last node that will be deleted ---------------------------- //

	t_list *isidor;
	char *fagioli = ft_strdup("Fagioli"); // malloc (through strdup) on that string, because I'll free it later
	isidor = ft_lstnew(fagioli);
	ft_lstadd_back(&alix, isidor);

	t_list *loop_ptr = alix;
	int node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
// ---------------------------- freeing the last created node ---------------------------- //

	mira->next = isidor->next;	// Updating the previous node's next address to the next address of the node we're about to delete (otherwise errors)
	ft_lstdelone(isidor, del); // I still don't get where this del funcion is coming from
	printf("\n*** After pass in DelOne function to erase the last node ***\n");
	loop_ptr = alix;
	node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node, loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
// --------------------------------------------------------------------------------------- //
	free(alix);
	free(cleo);
	free(mira);
	return(0);
} */
