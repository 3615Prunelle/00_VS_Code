#include "push_swap.h"

// ------------ ⬇️ Swap the first 2 elements at the top of stack a. Do nothing if there is only one element or none ✅
two_stacks		*swap_a(two_stacks	*a_and_b)
{
	if((ft_lstsize(a_and_b->stack_a) == 0) || (ft_lstsize(a_and_b->stack_a) == 1))
		return(NULL);

	linked_number *temp;						// Malloc pas nécessaire car temp is used only here
	temp = a_and_b->stack_a->next;				// ✅ Temp a les mêmes contenus que node 2
	a_and_b->stack_a->next = temp->next;		// ✅ Pour que le next du futur node 2, soit node 3
	temp->next = a_and_b->stack_a;				// ✅ Pour que temp next soit ex-head
	ft_lstadd_front(&a_and_b->head_a, temp);	// temp vient en tête de liste

	a_and_b->head_a = temp;
// ---------------- Vérif ✅ ----------------------------------------------------------------------------------------- //
	//verif("swap_a(inside)", a_and_b);
	return(a_and_b);
}

// ------------ ⬇️ Swap the first 2 elements at the top of stack b. Do nothing if there is only one element or none ✅
two_stacks		*swap_b(two_stacks	*a_and_b)
{
	if((ft_lstsize(a_and_b->stack_b) == 0) || (ft_lstsize(a_and_b->stack_b) == 1))
		return(NULL);

	linked_number *temp;						// Malloc pas nécessaire car temp is used only here
	temp = a_and_b->stack_b->next;				// ✅ Temp a les mêmes contenus que node 2
	a_and_b->stack_b->next = temp->next;		// ✅ Pour que le next du futur node 2, soit node 3
	temp->next = a_and_b->stack_b;				// ✅ Pour que temp next soit ex-head
	ft_lstadd_front(&a_and_b->head_b, temp);	// temp vient en tête de liste

	a_and_b->head_b = temp;
// ---------------- Vérif ✅ ----------------------------------------------------------------------------------------- //
	//verif("swap_b(inside)", a_and_b);
	return(a_and_b);
}

// ------------ ⬇️ sa and sb at the same time ✅
two_stacks		*swap_a_and_b(two_stacks *a_and_b)
{
	a_and_b = swap_a(a_and_b);
	a_and_b = swap_b(a_and_b);

// ---------------- Vérif ✅ ------------------------------------------------------------------------------------------- //
	//verif("Swap A&B (inside)", a_and_b);
	return(a_and_b);
}

// ------------ ⬇️ Take the first element at the top of b and put it at the top of a. Do nothing if b is empty ✅
two_stacks		*push_a(two_stacks *a_and_b)
{
	if(ft_lstsize(a_and_b->stack_b) == 0)
		return(NULL);

	// Update head b to stack b.next (do it before changing the position of stack b ?)
	a_and_b->head_b = a_and_b->stack_b->next;

	ft_lstadd_front(&a_and_b->head_a, a_and_b->stack_b);	// Head a pointer updated here ✅
	// lstadd front makes head b the new head of stack a = NO NEED TO UPDATE HEAD A POINTER
	// lstadd front updates next = NO NEED TO UPDATE THE NEXT ADDRESS

	// ---------------- Vérif ✅ ------------------------------------------------------------------------------------ //
	//verif("push_a (inside)", a_and_b);

	return(a_and_b);
}

// ------------ ⬇️ Take the first element at the top of a and put it at the top of b. Do nothing if a is empty ✅
two_stacks		*push_b(two_stacks *a_and_b)
{
	if(ft_lstsize(a_and_b->stack_a) == 0)
		return(NULL);

	a_and_b->head_a = a_and_b->stack_a->next;

	ft_lstadd_front(&a_and_b->head_b, a_and_b->stack_a);

	// ---------------- Vérif ✅ ------------------------------------------------------------------------------------ //
	verif("push_b (inside)", a_and_b);

	return(a_and_b);
}

// ------------ ⬇️ Shift up all elements of stack a by 1. The first element becomes the last one ✅
two_stacks		*rotate_a(two_stacks *a_and_b)
{
	// At this point, head a = stack a
	a_and_b->head_a = a_and_b->head_a->next;	// Head a correct ✅

	ft_lstadd_back(&a_and_b->head_a, a_and_b->stack_a);	// !! Doesn't set head a next to NULL
	a_and_b->stack_a->next = NULL;	// Faire ça après l'avoir déplacé, sinon le reste de la liste est inacessible (TBC)

	a_and_b->stack_a = a_and_b->head_a;

	return(a_and_b);
}

// ------------ ⬇️ Shift up all elements of stack b by 1. The first element becomes the last one ✅
two_stacks		*rotate_b(two_stacks *a_and_b)
{
	a_and_b->head_b = a_and_b->head_b->next;

	ft_lstadd_back(&a_and_b->head_b, a_and_b->stack_b);
	a_and_b->stack_b->next = NULL;

	a_and_b->stack_b = a_and_b->head_b;

	return(a_and_b);
}

// ------------ ⬇️ ra and rb at the same time ✅
two_stacks		*rotate_a_and_b(two_stacks *a_and_b)
{
	a_and_b = rotate_a(a_and_b);
	a_and_b = rotate_b(a_and_b);

	return(a_and_b);
}

// ------------ ⬇️ Shift down all elements of stack a by 1. The last element becomes the first one ❌
two_stacks		*reverse_rotate_a(two_stacks *a_and_b)
{
	linked_number	*last_node_stack_a;
	last_node_stack_a = ft_lstlast(a_and_b->head_a);		// Back up last node

	linked_number	*loop_ptr;
	loop_ptr = a_and_b->head_a;
	while (loop_ptr->next != NULL)							// Fetch l'avant dernier node
	{
		loop_ptr = loop_ptr->next;
	}
	loop_ptr->next = NULL;									// Make it the last one

	a_and_b->head_a = last_node_stack_a;					// Update head pointer
	last_node_stack_a->next = a_and_b->stack_a;				// Next is ex-first element of the list
	a_and_b->stack_a = a_and_b->head_a;						// Update stack a so it matches head a

	// Delete this when test ok
	//ft_lstadd_front(&a_and_b->head_a, last_node_stack_a);	// Last become first, head a + next pointers updated

	return(a_and_b);
}

// ------------ ⬇️ Shift down all elements of stack b by 1. The last element becomes the first one ❌
two_stacks		*reverse_rotate_b(two_stacks *a_and_b)
{

}

// ------------ ⬇️ rra and rrb at the same time ❌
two_stacks		*reverse_rotate_a_and_b(two_stacks *a_and_b)
{
	a_and_b = reverse_rotate_a(a_and_b);
	a_and_b = reverse_rotate_b(a_and_b);
	return(a_and_b);
}
/*
⬇️✅‼️⁉️Ⓜ️❓❌
*/
