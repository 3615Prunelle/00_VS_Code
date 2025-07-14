#include "push_swap.h"

int				main(void)
{
	int a[ARR_SIZE] = {100, 5, 500, 60};
	int b[ARR_SIZE] = {1, 444, 90, 2};

	if(is_number_repeat(a) || is_number_repeat(b))
	{
		printf("Duplicated number, edit and try again !\n");
		return(1);
	}

	two_stacks *a_and_b;
	a_and_b = malloc(sizeof(two_stacks));
	if(!a_and_b)
		return(1);

	a_and_b->stack_a = create_list(a);	// Ⓜ️🆓✅
	a_and_b->stack_b = create_list(b);	// Ⓜ️🆓✅

// -⬇️ ⁉️ Should I malloc these pointers ?
	a_and_b->head_a = a_and_b->stack_a;	// Update both head pointers at every op so they keep pointing at head stacks
	a_and_b->head_b = a_and_b->stack_b;

	printf("Head A address (won't change) : %p - Points to (supposedly head A) : %p (Current number : %i)\n", &a_and_b->head_a, a_and_b->head_a, *(int*)(a_and_b->head_a->content));
	printf("Head B address (won't change) : %p - Points to (supposedly head B) : %p (Current number : %i)\n", &a_and_b->head_b, a_and_b->head_b, *(int*)(a_and_b->head_b->content));

	verif("Initial Main", a_and_b);
	a_and_b = reverse_rotate_a(a_and_b);
	verif("Reverse Rotate A - Last becomes first", a_and_b);

	clean_exit(a_and_b);
	return(0);
}
