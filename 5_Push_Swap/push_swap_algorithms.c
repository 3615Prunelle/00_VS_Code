#include "push_swap.h"

void	sort_three(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter)
{ // Not using stack b
	if(lowest_number_index == 0)
	{
		REVROT_A;
		SWAP_A;
		if(highest_number_index == 2) // Without this line, issues when called from sort_four (if numbers are sorted)
			return;
		REVROT_A;
	}
	if(lowest_number_index == 1)
	{
		if(highest_number_index == 2)	// Et si le plus grand est déjà à la fin
			SWAP_A;
		else
			ROT_A;
	}
	if(lowest_number_index == 2)
		{
		if(highest_number_index == 0)
		{
			SWAP_A;
			REVROT_A;
		}
		else
			REVROT_A;
	}
}
void	sort_four(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter)
{
	if(lowest_number_index == 1)	// if position 0, only last push b necessary
	{
		SWAP_A;
	}
	if(lowest_number_index == 2)
	{
		ROT_A;
		ROT_A;
	}
	if(lowest_number_index == 3)
	{
		REVROT_A;
	}
	PUSH_B; // mettre smallest dans stack b et trier le reste avec sort_three

	int update_lowest; // updater car un nombre en moins, va fausser résultats de sort_three
	update_lowest = lowest_number_stack_index(STACK_A);

	int update_highest;
	update_highest = highest_number_stack_index(STACK_A);

	sort_three(update_lowest, update_highest, a_and_b, ops_counter);
	PUSH_A;
}
void	sort_five(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter)
{
	if(lowest_number_index == 1)	// if position 0, only last push b necessary
	{
		SWAP_A;
	}
	if(lowest_number_index == 2)
	{
		ROT_A;
		ROT_A;
	}
	if(lowest_number_index == 3)
	{
		REVROT_A;
		REVROT_A;
	}
	if(lowest_number_index == 4)
	{
		REVROT_A;
	}
	PUSH_B; // mettre smallest dans stack b et trier le reste avec sort_three
	int update_lowest; // updater car un nombre en moins, va fausser résultats de sort_three
	update_lowest = lowest_number_stack_index(STACK_A);
	int update_highest;
	update_highest = highest_number_stack_index(STACK_A);
	sort_four(update_lowest, update_highest, a_and_b, ops_counter);
	PUSH_A;

}

void	sort_above_five(two_stacks *a_and_b, int *ops_counter)
{
	int index_max = (ft_lstsize(a_and_b->stack_a));
	int i = 0;
	int bit_mask = 1;
	int highest_number = INT_MIN;

	while(true)
	{
		i = 0;
		while ((STACK_A != NULL) && (i < index_max))
		{
			if(STACK_A_CONTENT > highest_number)
			{
				highest_number = STACK_A_CONTENT;
			}

			if(!(STACK_A_CONTENT & bit_mask)) // Commencer à transférer les pairs dans stack b (last bit 0)
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
	return;
}

two_stacks	*add_int_max(two_stacks *a_and_b)
{
	// // Bloc below is just to test values
	// long int int_min = INT_MIN;
	// long int int_max = INT_MAX;

	// long int int_max_plus_one_without_cast = INT_MAX + 1;	//❌ No cast = Nope
	// long int int_casted_max_plus_one_test1 = (long int) INT_MAX + 1;	//✅
	// long int int_casted_max_plus_one_test2 = ((long int) INT_MAX) + 1;	//✅
	// long int int_casted_max_plus_one_test3 = (long int)(INT_MAX + 1);	//❌

	// long int sum_int_max_max = INT_MAX + INT_MAX;	//❌
	// long int sum_casted_int_max_max = (long int)INT_MAX + (long int)INT_MAX;	//✅ Cast = Evite l'overflow

	// long int sum_int_min_max_plus1 = INT_MIN + INT_MAX+1;	//✅		+1 because INT_MIN + INT_MAX = -1

	// long int long_max = LONG_MAX;	// ✅

	linked_number *loop_ptr;
	loop_ptr = STACK_A;
	while (loop_ptr != NULL)
	{
		*(long int*)(loop_ptr->content) += ((long int)(INT_MAX)) + 1;
		loop_ptr = loop_ptr->next;
	}
	return(a_and_b);
}

two_stacks	*substract_int_max(two_stacks *a_and_b)
{
	linked_number *loop_ptr;
	loop_ptr = STACK_A;
	while (loop_ptr != NULL)
	{
		*(long int*)(loop_ptr->content) -= ((long int)(INT_MAX)) + 1;
		loop_ptr = loop_ptr->next;
	}
	return(a_and_b);
}

void	sort_above_five_new(two_stacks *a_and_b, int *ops_counter)
{
	a_and_b = add_int_max(a_and_b);

	int index_max = (ft_lstsize(a_and_b->stack_a));
	int i = 0;
	int bit_mask = 1;
	int highest_number = INT_MIN;

	while(true)
	{
		i = 0;
		while ((STACK_A != NULL) && (i < index_max))
		{
			if(STACK_A_CONTENT > highest_number)
			{
				highest_number = STACK_A_CONTENT;
			}

			if(!(STACK_A_CONTENT & bit_mask)) // Commencer à transférer les pairs dans stack b (last bit 0)
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
	a_and_b = substract_int_max(a_and_b);
	return;
}
