#include "push_swap.h"

int			lowest_number_stack_index(linked_node *stack)
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

int			highest_number_stack_index(linked_node *stack)
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

linked_node	*add_index(int *numbers_array, int *array_size, linked_node *stack)
{
	int i = 0;
	int j = 0;
	int lower_numbers_counter = 0;
	linked_node *stack_copy = stack;

	while (i < *array_size)
	{
		j = 0;
		lower_numbers_counter = 0;
		while(j < *array_size)
		{
			if(numbers_array[i] > numbers_array[j])
			{
				lower_numbers_counter++;
			}
			j++;
		}
		stack_copy->index = lower_numbers_counter;	// change int for int* in struct if errors
		stack_copy = stack_copy->next;
		i++;
	}
	return(stack);
}

void		struct_config(int *numbers_array, int *array_size)
{
	int	ops_counter;
	ops_counter = 0;

	two_stacks *a_and_b;
	a_and_b = malloc(sizeof(two_stacks));		// Ⓜ️
	a_and_b->stack_a = NULL;
	a_and_b->stack_b = NULL;					// Pour éviter erreurs dans Valgrind

	if(!a_and_b)
		clean_early_exit(ERROR_MESSSAGE_06, numbers_array, true);		// ✅ All heap blocks were freed -- no leaks are possible

	STACK_A = create_stack(STACK_A, numbers_array, array_size);			// Ⓜ️ pour chaque node

	a_and_b = algorithm_selection(a_and_b, array_size, &ops_counter, numbers_array);

	// print_sorted_stack(a_and_b->stack_a);
	// printf("Operations counter : %i\n", ops_counter);
	// printf("Amount of numbers : %i\n", *array_size);

	// Ici, stack b == NULL, et on ne l'a pas malloc'é
	clean_exit("NULL", a_and_b, false);		// Can only go here because a_and_b doesn't exist in main
	free(numbers_array);
	return;
}

two_stacks 	*algorithm_selection(two_stacks *a_and_b, int *array_size, int *ops_counter, int *numbers_array)
{
	int lowest_number_index;
	int highest_number_index;
	int highest_number;

	lowest_number_index = lowest_number_stack_index(STACK_A);
	highest_number_index = highest_number_stack_index(STACK_A);
	highest_number = INT_MIN;

	if(*array_size == 2)
		swap_a(a_and_b, ops_counter);
	if(*array_size == 3)
		sort_three(lowest_number_index, highest_number_index, a_and_b, ops_counter);
	if(*array_size == 4)
		sort_four(lowest_number_index, highest_number_index, a_and_b, ops_counter);
	if(*array_size == 5)
		sort_five(lowest_number_index, highest_number_index, a_and_b, ops_counter);
	if(*array_size > 5)
	{
		add_index(numbers_array, array_size, STACK_A);
		sort_above_five(a_and_b, ops_counter, array_size, highest_number); // highest_number donné en param pour gratter 2 lignes
	}
	return(a_and_b);
}

char		*view_stack(linked_node *stack)
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
