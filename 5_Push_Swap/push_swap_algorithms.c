#include "push_swap.h"

void	algorithm_selection(long int numbers_array[], int array_size)
{
	if(array_size == 2)
	{
		ft_printf("\n___________\n\n%i %i\n___________\n", numbers_array[1], numbers_array[0]);	// Car s'ils étaient dans l'ordre, return already done
		clean_early_exit(NULL, false);
	}
	if(array_size == 3)
	{
		// Function
		//if((numbers_array[0] < numbers_array[1]) && (numbers_array[0] < numbers_array[1]))
		while(*numbers_array)
		{

		}
	}
	if(array_size == 4)
	{
		// Function
	}
	if(array_size == 5)
	{
		// Function
	}
	if(array_size > 5)
	{
		// Function
	}

	two_stacks *a_and_b;
	a_and_b = malloc(sizeof(two_stacks));					// Ⓜ️
	if(!a_and_b)
		clean_early_exit(ERROR_MESSSAGE_06, true);				// ✅ All heap blocks were freed -- no leaks are possible

	STACK_A = create_list(STACK_A, numbers_array, array_size);							// Ⓜ️ pour chaque node
	// check a push b to make sure it's ok if B doesn't exist yet

	ft_printf("\na_and_b pointer address\t%p (won't change)\nHolds this address	%p\nStack A is\t\t%p\nStack B is\t\t%p\n", &a_and_b, a_and_b, a_and_b->stack_a, a_and_b->stack_b);
	ft_printf("Head A pointer address\t%p (won't change)\nHolds Head A address\t%p (Current number : %i)\n", &STACK_A, STACK_A, *(int*)(STACK_A_CONTENT));

	verif("Initial Main", a_and_b);

// Make a small algorithm for small numbers (5 and less)
// Implement a condition for 2 numbers
// Create an algorithm for 3 numbers
// Create an algorithm for 4 numbers
// Create an algorithm for 5 numbers
// Create another algorithm for all other numbers

	// a_and_b = swap_a(a_and_b);
	// verif("swap_a", a_and_b);
	// a_and_b = swap_b(a_and_b);
	// verif("swap_b", a_and_b);
	// a_and_b = swap_a_and_b(a_and_b);
	// verif("swap_a_and_b", a_and_b);
	// a_and_b = push_a(a_and_b);
	// verif("push_a", a_and_b);
	// a_and_b = rotate_a(a_and_b);
	// verif("rotate_a", a_and_b);
	// a_and_b = push_b(a_and_b);
	// verif("push_b", a_and_b);
	// a_and_b = rotate_b(a_and_b);
	// verif("rotate_b", a_and_b);
	// a_and_b = reverse_rotate_a(a_and_b);
	// verif("reverse_rotate_a", a_and_b);
	// a_and_b = reverse_rotate_b(a_and_b);
	// verif("reverse_rotate_b", a_and_b);
	// a_and_b = rotate_a_and_b(a_and_b);
	// verif("rotate_a_and_b", a_and_b);
	// a_and_b = reverse_rotate_a_and_b(a_and_b);
	// verif("Last _ reverse_rotate_a_and_b", a_and_b);

	clean_exit(NULL, a_and_b, false);		// Can only go here because a_and_b doesn't exist in main

	return;
}
