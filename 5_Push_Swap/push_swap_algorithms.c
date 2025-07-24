#include "push_swap.h"

void	sort_three(int *numbers_array, two_stacks *a_and_b, int *ops_counter)
{
	char *coucou;
	coucou = view_stack(a_and_b->stack_a);
	ft_printf("%s\n", coucou);

	if((numbers_array[0] < numbers_array[1]) && (numbers_array[0] < numbers_array[2]))		// Si le plus petit est à l'index 0
	{
		PUSH_B;
		SWAP_A;
	}
	if((numbers_array[1] < numbers_array[0]) && (numbers_array[1] < numbers_array[2]))		// Si le plus petit est à l'index 1
	{
		SWAP_A;
		PUSH_B;
		if(numbers_array[0] > numbers_array[2])
		{
			SWAP_A;
		}
	}
	if((numbers_array[2] < numbers_array[0]) && (numbers_array[2] < numbers_array[1]))		// Si le plus petit est à l'index 2
	{
		REVROT_A;
		PUSH_B;
		if(numbers_array[0] > numbers_array[1])
		{
			SWAP_A;
		}
	}
	PUSH_A;
	return;
}
void	sort_four(int *numbers_array, two_stacks *a_and_b)
{

}
void	sort_five(int *numbers_array, two_stacks *a_and_b)
{

}

void	sort_all(int *numbers_array, two_stacks *a_and_b, int *ops_counter)
{
	int index_max = (ft_lstsize(a_and_b->stack_a));
	int i = 0;
	int bit_mask = 1;
	int highest_number = INT_MIN;

	while(true)
	{
		while ((STACK_A != NULL) && (i < index_max))
		{
			if(STACK_A_CONTENT > highest_number)
			{
				highest_number = STACK_A_CONTENT;
			}

			if(STACK_A_CONTENT & bit_mask) // Commencer à transférer les plus grands dans stack b (1)
			{
				PUSH_B;
			}
			else
				ROT_A;
			i++;
		}
		while (STACK_B != NULL)
		{
			PUSH_A;
		}
		bit_mask *= 2;
		if(bit_mask > highest_number)
		{
			break;
		}
	}
	// Ici, tout est théoriquement trié dans la stack
	print_sorted_stack(a_and_b);
	return;
}
bool	is_stack_sorted(linked_number *stack)
{
	int	repere = INT_MIN;

}

void	algorithm_selection(int *numbers_array, int array_size)
{
/* 	ft_printf("Numbers to sort :\n");
	int i = 0;
	while(i < array_size)
	{
		ft_printf("[ %i ]\n", numbers_array[i]);
		i++;
	} */
	int	*ops_counter;
	ops_counter = malloc(sizeof(int));
	*ops_counter = 0;

	two_stacks *a_and_b;
	a_and_b = malloc(sizeof(two_stacks));					// Ⓜ️
	if(!a_and_b)
		clean_early_exit(ERROR_MESSSAGE_06, true);			// ✅ All heap blocks were freed -- no leaks are possible

	STACK_A = create_list(STACK_A, numbers_array, array_size);							// Ⓜ️ pour chaque node

	if(array_size == 2)
	{
		swap_a(a_and_b, ops_counter);		// 1 operaton vs. 2 for the sort_all function
		print_sorted_stack(a_and_b);
	}
	if(array_size == 3)
	{
		sort_all(numbers_array, a_and_b, ops_counter);
//		sort_three(numbers_array, a_and_b, ops_counter);
		print_sorted_stack(a_and_b);
	}
	if(array_size == 4)
	{
		sort_four(numbers_array, a_and_b);
	}
	if(array_size == 5)
	{
		sort_five(numbers_array, a_and_b);
	}
	if(array_size > 5)
	{
		sort_all(numbers_array, a_and_b, ops_counter);
	}

	ft_printf("Operations counter : %i\n", *ops_counter);

	clean_exit(NULL, a_and_b, false);		// Can only go here because a_and_b doesn't exist in main

	return;
}
