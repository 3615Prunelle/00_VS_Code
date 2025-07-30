#include "push_swap.h"

bool		is_number_repeat(int *numbers_array, int array_size)
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

linked_node	*create_stack(linked_node *stack, int *numbers_array, int *array_size)
{
	stack = new_node(&numbers_array[0]);

	linked_node *new;
	int i = 1;

	while (i < *array_size)
	{
		new = new_node(&numbers_array[i]);		// On créée des nodes sans nom à la chaine + malloc du node (! pas du content)
		add_node_down(&stack, new);
		i++;
	}
	return(stack);
}

void		clean_early_exit(char *message, int *numbers_array, bool exit_wanted)
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
void		clean_exit(char *message, two_stacks *a_and_b, bool exit_wanted)
{
	linked_node	*loop_pointer;
	linked_node	*backup_next;

	if(a_and_b)
	{
		if(STACK_A)		// No need for stack b, car il n'a (à priori) jamais été malloc'é
		{
			loop_pointer = STACK_A;
			while(loop_pointer != NULL)
			{
				backup_next = loop_pointer->next;
				free(loop_pointer);
				loop_pointer = backup_next;
			}
			STACK_A = NULL;
			free(a_and_b);
			a_and_b = NULL;
		}
	}
	if(exit_wanted)
	{
		ft_printf("%s\n", message);
		exit(1);
	}
}

void		print_sorted_stack(linked_node *stack)
{
	while(stack != NULL)
	{
		printf("%i ", *(int*)(stack->content));	// Use only for tests, ne marche pas avec mon ft_printf
		fflush(stdout);
		stack = stack->next;
	}
	ft_printf("\n\n");
}
