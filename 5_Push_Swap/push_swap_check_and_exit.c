#include "push_swap.h"

bool			is_number_repeat(long int *numbers_array, int array_size)
{
	int i = 0;
	int j;
	int count_occurences;

	while(i < array_size)
	{
		j = 0;
		count_occurences = 0;			// Reset pour chaque nombre
		while (j < array_size)
		{
			if(numbers_array[i] == numbers_array[j])
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

linked_number	*create_list(linked_number *stack, long int *numbers_array, int array_size)
{
	stack = ft_lstnew(&numbers_array[0]);
// ⬇️ NB pour print : content est un pointeur, mais on veut print un int, donc il faut le caster ET le déréférencer
	// ft_printf("Just created Head	Number	%i	Next	%p\n", *(int *)(stack->content), stack->next);

	linked_number *new;
	int i = 1;

	while (i < array_size)
	{
		new = ft_lstnew(&numbers_array[i]);		// On créée des nodes sans nom à la chaine + malloc du node (! pas du content)
		ft_lstadd_back(&stack, new);
		// ft_printf("Just created Node %i	Number	%i	Next	%p\n", i, *(int *)(new->content), new->next);
		i++;
	}
	// ft_printf("Head	Number	%i	Next	%p\n", *(int *)(stack->content), stack->next);

	return(stack);
}

void			clean_early_exit(char *message, long int *numbers_array, bool exit_wanted)
{
	if(numbers_array)
		free(numbers_array);

	if(exit_wanted)
	{
		ft_printf("%s\n", message);
		exit(1);
	}
}

// ------------ ⬇️ NB : Don't use ft_lstclear because it frees node + content (and no content was allocated)
void			clean_exit(char *message, two_stacks *a_and_b, bool exit_wanted)
{
	linked_number	*loop_pointer;
	linked_number	*backup_next;

	if(a_and_b)
	{
		if(STACK_A)
		// if(a_and_b)
		{
			loop_pointer = STACK_A;
			while(loop_pointer != NULL)
			{
				backup_next = loop_pointer->next;
				free(loop_pointer);
				loop_pointer = backup_next;
			}
			STACK_A = NULL;
		}
		// if(STACK_B)			// No need, car stack b n'a (à priori) jamais été malloc'ée
		// // if(a_and_b)
		// {
		// 	loop_pointer = STACK_B;
		// 	while(loop_pointer != NULL)
		// 	{
		// 		backup_next = loop_pointer->next;
		// 		free(loop_pointer);
		// 		loop_pointer = backup_next;
		// 	}
		// 	STACK_B = NULL;
		// }
	}

	if(a_and_b)
	{
		free(a_and_b);
		a_and_b = NULL;
	}
	if(exit_wanted)
	{
		ft_printf("%s\n", message);
		exit(1);
	}
}

void			verif(char *fonction, two_stacks *a_and_b)
{
	ft_printf("\n\t*** Pass in %s ***\n", fonction);
	int i = 0;
	linked_number *loop_ptr;	// Trick pour ne pas avoir à nommer les nodes (car après head, ils n'ont pas de nom)

	if(a_and_b)					// Avoids issues when stack is empty
	{
		ft_printf("\n\tSTACK A\n");
		loop_ptr = STACK_A;
		while (loop_ptr != NULL)
		{
			ft_printf("Node [%i]\t%i\t%p\tNext\t%p\n", i, *(int *)(loop_ptr->content), loop_ptr, loop_ptr->next);
			loop_ptr = loop_ptr->next;
			i++;
		}
		if(STACK_B != NULL)		// Avoids issues when stack is empty
			ft_printf("Stack A pointer is currently number : %i\n", STACK_A_CONTENT);
	}
	if(a_and_b)
	{
		ft_printf("\n\tSTACK B\n");
		i = 0;
		loop_ptr = STACK_B;
		while (loop_ptr != NULL)
		{
			ft_printf("Node [%i]\t%i\t%p\tNext\t%p\n", i, *(int *)(loop_ptr->content), loop_ptr, loop_ptr->next);
			loop_ptr = loop_ptr->next;
			i++;
		}
		if(STACK_B != NULL)
			ft_printf("Stack B pointer is currently number : %i\n", *(int*)(STACK_B_CONTENT));
	}
}

void			ex_print_sorted_stack(two_stacks *a_and_b)
{
	if(STACK_B)
	{
		ft_printf("Stack B is not empty\n");
		return;
	}
	if(STACK_A)
	{
		while(STACK_A != NULL)
		{
			ft_printf("%i ", STACK_A_CONTENT);
			STACK_A = STACK_A_NEXT;
		}
	}
	ft_printf("\n\n");
}

void			print_sorted_stack(linked_number *stack)
{
	while(stack != NULL)
	{
		printf("%i ", *(int*)(stack->content));	// Use only for tests, ne marche pas avec mon ft_printf
		fflush(stdout);
		stack = stack->next;
	}
	ft_printf("\n\n");
}

