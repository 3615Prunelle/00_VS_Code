#include "push_swap.h"

bool			is_number_repeat(int array[])
{
	int i = 0;
	int j;
	int count_occurences;

	while(i < ARR_SIZE)
	{
		j = 0;
		count_occurences = 0;			// Reset pour chaque nombre
		while (j < ARR_SIZE)
		{
			if(array[i] == array[j])
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

two_stacks		*swap_a(two_stacks	*a_and_b)	// ------------------------------------------------------------------------- ✅
{
// sa or sb : Swap the first 2 elements at the top of stack. Do nothing if there is only one element or none.
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

two_stacks		*swap_b(two_stacks	*a_and_b)	// ------------------------------------------------------------------------- ✅
{
// sa or sb : Swap the first 2 elements at the top of stack. Do nothing if there is only one element or none.
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

two_stacks		*swap_a_and_b(two_stacks *a_and_b)	// ----------------------------------------------------------------- ✅
{
	a_and_b = swap_a(a_and_b);
	a_and_b = swap_b(a_and_b);

// ---------------- Vérif ✅ ------------------------------------------------------------------------------------------- //
	//verif("Swap A&B (inside)", a_and_b);
	return(a_and_b);
}

two_stacks		*push_a(two_stacks *a_and_b)
{
	/*Take the first element at the top of b and put it at the top of a.
	Do nothing if b is empty.*/

	if(ft_lstsize(a_and_b->stack_b) == 0)
		return(NULL);

	// Update head b to stack b.next (do it before changing the position of stack b ?)
	a_and_b->head_b = a_and_b->stack_b->next;

	ft_lstadd_front(&a_and_b->head_a, a_and_b->stack_b);	// Head a correct ✅
	// lstadd front makes head b the new head of stack a - NO NEED TO UPDATE HEAD A POINTER
	// lstadd front updates next - NO NEED TO UPDATE THE NEXT ADDRESS
	// head b is now head a

	// ---------------- Vérif ❌ ✅ ------------------------------------------------------------------------------------ //
	verif("push_a (inside)", a_and_b);

	return(a_and_b);
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
	return(head);
}

void			verif(char *fonction, two_stacks *a_and_b)
{
	printf("\n*** Pass in %s ***\n", fonction);
	int i = 0;
	linked_number *loop_ptr;	// Trick pour ne pas avoir à nommer les nodes (car après head, ils n'ont pas de nom)

	printf("\n	STACK A\n");
	loop_ptr = a_and_b->head_a;
	while (loop_ptr->next != NULL)
	{
		printf("Node %i	Number	%i	Next	%i\n", i, *(int *)(loop_ptr->content), *(int *)(loop_ptr->next->content));
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf("Head pointer is currently number : %i\n", *(int*)(a_and_b->head_a->content));
	printf("\n	STACK B\n");
	i = 0;
	loop_ptr = a_and_b->head_b;
	while (loop_ptr->next != NULL)
	{
		printf("Node %i	Number	%i	Next	%i\n", i, *(int *)(loop_ptr->content), *(int *)(loop_ptr->next->content));
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf("Head pointer is currently number : %i\n", *(int*)(a_and_b->head_b->content));
}

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

	a_and_b->stack_a = create_list(a);
	a_and_b->stack_b = create_list(b);

	a_and_b->head_a = a_and_b->stack_a;	// Update both head pointers at every op so they keep pointing at head stacks
	a_and_b->head_b = a_and_b->stack_b;

	printf("Head A address (won't change) : %p - Points to (supposedly head A) : %p (Current number : %i)\n", &a_and_b->head_a, a_and_b->head_a, *(int*)(a_and_b->head_a->content));
	printf("Head B address (won't change) : %p - Points to (supposedly head B) : %p (Current number : %i)\n", &a_and_b->head_b, a_and_b->head_b, *(int*)(a_and_b->head_b->content));

	verif("Initial Main", a_and_b);
	a_and_b = push_a(a_and_b);
	verif("push_a (outside)", a_and_b);

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
