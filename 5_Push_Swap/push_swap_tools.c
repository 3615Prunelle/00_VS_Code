#include "push_swap.h"

int		ex_smallest_number(long int *numbers_array, two_stacks *a_and_b)
{
	int smallest = INT_MAX;
	int i = 0;
	int lowest_number_index;
	int array_size;
	array_size = ft_lstsize(a_and_b->stack_a);

	while (i < array_size)
	{
		if(*numbers_array < smallest)
		{
			smallest = *numbers_array;
			lowest_number_index = i;
		}
		numbers_array++;
		i++;
	}
	return(lowest_number_index);
}

int		lowest_number_stack_index(linked_number *stack)
{
	int i = 0;
	int lowest_number = INT_MAX;
	int	lowest_number_index;

	while (stack != NULL)
	{
		if(*(int*)(stack->content) < lowest_number)
		{
			lowest_number = *(int*)(stack->content);
			lowest_number_index = i;
		}
		i++;
		stack = stack->next;
	}
	return(lowest_number_index);
}

int		highest_number_stack_index(linked_number *stack)
{
	int i = 0;
	int highest_number = INT_MIN;
	int	highest_number_index;

	while (stack != NULL)
	{
		if(*(int*)(stack->content) > highest_number)
		{
			highest_number = *(int*)(stack->content);
			highest_number_index = i;
		}
		i++;
		stack = stack->next;
	}
	return(highest_number_index);
}

int		*list_to_array(int *new_array, linked_number *stack)
{
	int	array_size;
	array_size = ft_lstsize(stack);
	int i = 0;

	while(i < array_size)
	{
		new_array[i] = *((int *)(stack->content));
		stack = stack->next;
		i++;
	}
	return(new_array);
}

void	algorithm_selection(long int *numbers_array, int array_size)
{
	int	*ops_counter;
	ops_counter = malloc(sizeof(int));
	*ops_counter = 0;

	two_stacks *a_and_b;
	a_and_b = malloc(sizeof(two_stacks));					// Ⓜ️
	a_and_b->stack_a = NULL;
	a_and_b->stack_b = NULL;				// Pour éviter erreurs dans Valgrind

	if(!a_and_b)
		clean_early_exit(ERROR_MESSSAGE_06, numbers_array, true);			// ✅ All heap blocks were freed -- no leaks are possible

	STACK_A = create_list(STACK_A, numbers_array, array_size);							// Ⓜ️ pour chaque node

	int lowest_number_index;
	lowest_number_index = lowest_number_stack_index(STACK_A);

	int highest_number_index;
	highest_number_index = highest_number_stack_index(STACK_A);

	if(array_size == 2)
	{
		swap_a(a_and_b, ops_counter);		// 1 operations vs. 2 for the sort_above_five function
	}
	if(array_size == 3)
	{
		sort_three(lowest_number_index, highest_number_index, a_and_b, ops_counter);	// 4 max operations vs. +++ for the sort_above_five function
	}
	if(array_size == 4)
	{
		sort_four(lowest_number_index, highest_number_index, a_and_b, ops_counter);		// 5 max operations vs. +++ for the sort_above_five function
	}
	if(array_size == 5)
	{
		sort_five(lowest_number_index, highest_number_index, a_and_b, ops_counter);
	}
	if(array_size > 5)
	{
		sort_above_five(a_and_b, ops_counter);
	}

	print_sorted_stack(a_and_b->stack_a);
	ft_printf("Operations counter : %i\n", *ops_counter);

	// Ici, stack b == NULL, et on ne l'a pas malloc'é
	clean_exit("NULL", a_and_b, false);		// Can only go here because a_and_b doesn't exist in main
	free(ops_counter);
	free(numbers_array);
	return;
}

char	*view_stack(linked_number *stack)
{
	char *string_finale = "";	// Evite le malloc / segfault
	char *espace = " ";
	char *conv_nombre;
	while(stack != NULL)
	{
		conv_nombre = ft_itoa(*(int*)(stack->content));
		string_finale = ft_strjoin(string_finale, conv_nombre);
		string_finale = ft_strjoin(string_finale, espace);
		stack = stack->next;
	}
	return(string_finale);
}
