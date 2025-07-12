#include "push_swap.h"

bool			is_number_repeat(linked_number *stack)
{

}

linked_number	*swap(linked_number *stack)	// ---------------------------------------------------------------------- ✅
{
// sa or sb : Swap the first 2 elements at the top of stack. Do nothing if there is only one element or none.
	if((ft_lstsize(stack) == 0) || (ft_lstsize(stack) == 1))
		return(NULL);

	linked_number *temp;			// ⁉️ Malloc nécessaire ?
	temp = stack->next;				// ✅ Temp a les mêmes contenus que node 2 (5 + next 874)
	stack->next = temp->next;		// ✅ Pour que le next du futur node 2, soit node 3
	temp->next = stack;				// ✅ Pour que temp next soit ex-head
	ft_lstadd_front(&stack, temp);	// temp vient en tête de liste

// ---------------- Vérif ✅ ---------------------------------------------------------------------------------------- //
	//verif("swap", stack);
	return(stack);
}

two_stacks		*swap_a_and_b(linked_number *stack_a, linked_number *stack_b)	// -------------------------------------- ✅
{
	two_stacks *double_return;
	double_return = malloc(sizeof(double_return));
	if(!double_return)
		return(NULL);

	double_return->stack_a = swap(stack_a);
	double_return->stack_b = swap(stack_b);

// ---------------- Vérif ✅ ---------------------------------------------------------------------------------------- //
//	verif("Swap AB for stack A", double_return->stack_a);
//	verif("Swap AB for stack B", double_return->stack_b);
	return(double_return);
}

void			push_a(linked_number *stack_a, linked_number *stack_b)
{
	/*Take the first element at the top of b and put it at the top of a.
	Do nothing if b is empty.*/

// ---------------- Vérif ❌ ✅ ------------------------------------------------------------------------------------- //
	// verif("", stack);

}
linked_number	*create_list(int array[])
{
	linked_number *head;				// ⁉️ Malloc nécessaire ?
	head = ft_lstnew(&array[0]);
// NB : content est un pointeur, mais on veut print un int, donc il faut le caster ET le déréférencer
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
// ---------------- Vérif ✅ ---------------------------------------------------------------------------------------- //
//	verif("Initialization loop", head);
	return(head);
}

void			verif(char *fonction, linked_number *stack)
{
	printf("\n*** Pass in %s ***\n", fonction);
	int i = 0;
	linked_number *loop_ptr;	// Trick pour ne pas avoir à nommer les nodes (car après head, ils n'ont pas de nom)
	loop_ptr = stack;
	while (loop_ptr->next != NULL)
	{
		printf("Node %i	Number	%i	Next	%i\n", i, *(int *)(loop_ptr->content), *(int *)(loop_ptr->next->content));
		loop_ptr = loop_ptr->next;
		i++;
	}
}

int				main(void)
{
	int a[ARR_SIZE] = {100, 5, 444, 6, 7, 8, 9, 10};
	int b[ARR_SIZE] = {1, 500, 90, 2, 3, 4, 5, 6};

	linked_number *stack_a = create_list(a);
	linked_number *stack_b = create_list(b);

	verif("Initial Main", stack_a);

/* 	two_stacks *double_return;
	double_return = swap_a_and_b(stack_a, stack_b);
	stack_a = double_return->stack_a;
	stack_b = double_return->stack_b; */


	return(0);
}

/*
🟡 sa (swap a): Swap the first 2 elements at the top of stack a.
	Do nothing if there is only one element or none.
🟡 sb (swap b): Swap the first 2 elements at the top of stack b.
	Do nothing if there is only one element or none.
🟡 ss : sa and sb at the same time.
🟡 pa (push a): Take the first element at the top of b and put it at the top of a.
	Do nothing if b is empty.
🟡 pb (push b): Take the first element at the top of a and put it at the top of b.
	Do nothing if a is empty.
🟡 ra (rotate a): Shift up all elements of stack a by 1.
	The first element becomes the last one.
🟡 rb (rotate b): Shift up all elements of stack b by 1.
	The first element becomes the last one.
🟡 rr : ra and rb at the same time.
🟡 rra (reverse rotate a): Shift down all elements of stack a by 1.
🟡 The last element becomes the first one.
🟡 rrb (reverse rotate b): Shift down all elements of stack b by 1.
	The last element becomes the first one.
🟡 rrr : rra and rrb at the same time.
*/
