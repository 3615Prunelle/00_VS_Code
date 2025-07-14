#include "push_swap.h"

bool			is_number_repeat(int array[])
{
	int i = 0;
	int j;
	int count_occurences;

	while(i < ARR_SIZE)
	{
		j = 0;
		count_occurences = 0;			// Reset pour chaque nombre
		while (j < ARR_SIZE)
		{
			if(array[i] == array[j])
			{
				count_occurences++;
					if(count_occurences > 1)
						return(true);
			}
			j++;
		}
		i++;
	}
	return(false);
}

linked_number	*create_list(int array[])
{
	linked_number *head;
	head = malloc(sizeof(linked_number));	// ⁉️ Malloc nécessaire ?
	if(!head)
		return(NULL);
	head = ft_lstnew(&array[0]);
// ⬇️ NB : content est un pointeur, mais on veut print un int, donc il faut le caster ET le déréférencer
//	printf("Just created Head	Number	%i	Next	%p\n", *(int *)(head->content), head->next);

	linked_number *new;
	int i = 1;

	while (i < ARR_SIZE)
	{
		new = ft_lstnew(&array[i]);		// On créée des nodes sans nom à la chaine
		ft_lstadd_back(&head, new);
//		printf("Just created Node %i	Number	%i	Next	%p\n", i, *(int *)(new->content), new->next);
		i++;
	}
	return(head);
}

void			clean_exit(two_stacks *a_and_b)
{
/* 	if(a_and_b->head_a)
		free(a_and_b->head_a);
	if(a_and_b->head_b)
		free(a_and_b->head_b); */		// This part might not be necessary because I don't malloc these pointers (should I ?)
	if(a_and_b->stack_a)
		free(a_and_b->stack_a);
	if(a_and_b->stack_b)
		free(a_and_b->stack_b);
	if(a_and_b)
		free(a_and_b);
}

void			verif(char *fonction, two_stacks *a_and_b)
{
	printf("\n*** Pass in %s ***\n", fonction);
	int i = 0;
	linked_number *loop_ptr;	// Trick pour ne pas avoir à nommer les nodes (car après head, ils n'ont pas de nom)

	printf("\n	STACK A\n");
	loop_ptr = a_and_b->head_a;
	while (loop_ptr->next != NULL)
	{
		printf("Node %i	Number	%i	Next	%i\n", i, *(int *)(loop_ptr->content), *(int *)(loop_ptr->next->content));
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf("Head pointer is currently number : %i\n", *(int*)(a_and_b->head_a->content));
	printf("Stack A pointer is currently number : %i\n", *(int*)(a_and_b->stack_a->content));
	printf("\n	STACK B\n");
	i = 0;
	loop_ptr = a_and_b->head_b;
	while (loop_ptr->next != NULL)
	{
		printf("Node %i	Number	%i	Next	%i\n", i, *(int *)(loop_ptr->content), *(int *)(loop_ptr->next->content));
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf("Head pointer is currently number : %i\n", *(int*)(a_and_b->head_b->content));
	printf("Stack B pointer is currently number : %i\n", *(int*)(a_and_b->stack_b->content));
}
