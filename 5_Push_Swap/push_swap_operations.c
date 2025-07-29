#include "push_swap.h"

// ------------ ⬇️ Swap the first 2 elements at the top of stack a. Do nothing if there is only one element or none ✅
two_stacks		*swap_a(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("sa\n");
	// if((count_nodes(STACK_A) == 0) || (count_nodes(STACK_A) == 1))
	if((STACK_A == NULL) || (count_nodes(STACK_A) == 1))
		return(a_and_b);

	linked_node	*backup_node1;			// Will become new_node_2
	backup_node1 = STACK_A;

	linked_node	*node2;					// Malloc pas nécessaire car node2 is used only here
	node2 = STACK_A_NEXT;

	// Next à changer pour node 3 avant toute opération
	backup_node1->next = node2->next;

	// ⬇️ addfront s'occupe de mettre le bon next pour le newfirstnode (node2) + update le ptr du stack (head)
	add_node_up(&STACK_A, node2);		// node2 vient en tête de liste
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Swap the first 2 elements at the top of stack b. Do nothing if there is only one element or none ✅
two_stacks		*swap_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("sb\n");
	// if((count_nodes(STACK_B) == 0) || (count_nodes(STACK_B) == 1))
	if((STACK_B == NULL) || (count_nodes(STACK_B) == 1))
		return(a_and_b);

	linked_node	*backup_node1;			// See all notes in swap_a function
	backup_node1 = STACK_B;

	linked_node	*node2;
	node2 = STACK_B_NEXT;

	backup_node1->next = node2->next;

	add_node_up(&STACK_B, node2);
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ sa and sb at the same time ✅
two_stacks		*swap_a_and_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("ss\n");
	a_and_b = swap_a(a_and_b, ops_counter);
	a_and_b = swap_b(a_and_b, ops_counter);
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Take the first element at the top of b and put it at the top of a. Do nothing if b is empty ✅
two_stacks		*push_a(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("pa\n");
	if(STACK_B == NULL) // count_nodes(STACK_B) == 0) donnait des memory leaks
		return(a_and_b);

	linked_node	*backup_node1b;
	backup_node1b = STACK_B;

//  ⬇️ Update B pointer because I don't use lstaddfront on this stack
	STACK_B = backup_node1b->next;

//  ⬇️ Everything A-related wil be updated correctly
	add_node_up(&STACK_A, backup_node1b);
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Take the first element at the top of a and put it at the top of b. Do nothing if a is empty ✅
two_stacks		*push_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("pb\n");
	if(STACK_A == NULL) // count_nodes(STACK_A) == 0) donnait des memory leaks
		return(a_and_b);

	linked_node	*backup_node1a;
	backup_node1a = STACK_A;

//  ⬇️ Update A pointer because I don't use lstaddfront on this stack
	STACK_A = backup_node1a->next;

//  ⬇️ Everything B-related wil be updated correctly
	add_node_up(&STACK_B, backup_node1a);
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Shift up all elements of stack a by 1. The first element becomes the last one ✅
two_stacks		*rotate_a(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("ra\n");
	if((STACK_A == NULL) || (STACK_A_NEXT == NULL))
		return(a_and_b);

	linked_node	*backup_node1;
	backup_node1 = STACK_A;

	linked_node	*backup_node2;
	backup_node2 = STACK_A_NEXT;

	STACK_A = backup_node2;

	add_node_down(&STACK_A, backup_node1);

	backup_node1->next = NULL;					// Always do that at the end
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Shift up all elements of stack b by 1. The first element becomes the last one ✅
two_stacks		*rotate_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("rb\n");
	if((STACK_B == NULL) || (STACK_B_NEXT == NULL))
		return(a_and_b);

	linked_node	*backup_node1;
	backup_node1 = STACK_B;

	linked_node	*backup_node2;
	backup_node2 = STACK_B_NEXT;

	STACK_B = backup_node2;

	add_node_down(&STACK_B, backup_node1);

	backup_node1->next = NULL;					// Always do that at the end
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ ra and rb at the same time ✅
two_stacks		*rotate_a_and_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("rr\n");
	a_and_b = rotate_a(a_and_b, ops_counter);
	a_and_b = rotate_b(a_and_b, ops_counter);
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Shift down all elements of stack a by 1. The last element becomes the first one ✅
two_stacks		*reverse_rotate_a(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("rra\n");
	linked_node	*loop_ptr;
	loop_ptr = STACK_A;

	if((STACK_A == NULL) || (STACK_A_NEXT == NULL))
		return(a_and_b);			// Condition à déplacer dans fonction appelante car elle s'applique à toutes les autres operations

	while (loop_ptr->next->next != NULL)	// Fetch l'avant dernier node
	{
		loop_ptr = loop_ptr->next;
	}
	linked_node	*last_node;
	last_node = loop_ptr->next;
	loop_ptr->next = NULL;					// Make it the last one

	last_node->next = STACK_A;				// Next is ex-first element of the list
	STACK_A = last_node;					// Update head pointer
	(*ops_counter)++;
	return(a_and_b);
}

// ------------ ⬇️ Shift down all elements of stack b by 1. The last element becomes the first one ✅
two_stacks		*reverse_rotate_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("rrb\n");
	linked_node	*loop_ptr;
	loop_ptr = STACK_B;

	if((STACK_B == NULL) || (STACK_B_NEXT == NULL))		// Si la linked list ne contient qu'un élément
		return(a_and_b);					// Condition à déplacer dans fonction appelante car elle s'applique à toutes les autres operations

	while (loop_ptr->next->next != NULL)	// Fetch l'avant dernier node
	{
		loop_ptr = loop_ptr->next;
	}
	linked_node	*last_node;
	last_node = loop_ptr->next;
	loop_ptr->next = NULL;					// Make it the last one

	last_node->next = STACK_B;		// Next is ex-first element of the list
	STACK_B = last_node;			// Update head pointer
	(*ops_counter)++;
	return(a_and_b);

}

// ------------ ⬇️ rra and rrb at the same time ✅
two_stacks		*reverse_rotate_a_and_b(two_stacks *a_and_b, int *ops_counter)
{
	ft_printf("rrr\n");
	a_and_b = reverse_rotate_a(a_and_b, ops_counter);
	a_and_b = reverse_rotate_b(a_and_b, ops_counter);
	(*ops_counter)++;
	return(a_and_b);
}
