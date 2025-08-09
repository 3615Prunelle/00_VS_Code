/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:05:12 by sophie            #+#    #+#             */
/*   Updated: 2025/08/09 10:04:21 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// on check l'index du 1er node au lieu de (méthode précédente) checker l'index du lowest number
// pas mis le premier 'if (a_b->stack_a->next->index == 1)' car si on arrive ici,
// c'est que next->next->index est 2 = les nombres sont dans l'ordre
void	sort_three(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->index == 0)
	{
		if (a_b->stack_a->next->index == 2)
		{
			swap_a(a_b, ops_counter);
			rotate_a(a_b, ops_counter);
		}
	}
	if (a_b->stack_a->index == 1)
	{
		if (a_b->stack_a->next->index == 0)
			swap_a(a_b, ops_counter);
		else if (a_b->stack_a->next->index == 2)
			reverse_rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->index == 2)
	{
		rotate_a(a_b, ops_counter);
		if (a_b->stack_a->next->index == 1)
			swap_a(a_b, ops_counter);
	}
	return;
}

// If lowest number position 0, only last push b necessary
// push_b = mettre smallest dans stack b et trier le reste avec sort_three
void	sort_four(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->next->index == 0)
	{
		swap_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->index == 0)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
	}
	push_b(a_b, ops_counter);
	add_update_index(a_b->stack_a);
	sort_three(a_b, ops_counter);
	push_a(a_b, ops_counter);
}

// If lowest number position 0, only last push b necessary
// push_b = mettre smallest dans stack b et trier le reste avec sort_four (qui appelle sort_three)
void	sort_five(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->next->index == 0)
	{
		swap_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->index == 0)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
		reverse_rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
	}
	push_b(a_b, ops_counter);
	add_update_index(a_b->stack_a);
	sort_four(a_b, ops_counter);
	push_a(a_b, ops_counter);
}
// Uniquement pour les fonctions <= 5 params
t_node	*add_update_index(t_node *stack)
{
	int		lower_numbers_counter;
	t_node	*stack_compare;
	t_node	*looping_pointer;

	stack_compare = malloc(sizeof(t_node));
	looping_pointer = stack;
	stack_compare->content = looping_pointer->content;
	stack_compare->next = looping_pointer->next;

	while (looping_pointer != NULL)
	{
		stack_compare = stack;
		lower_numbers_counter = 0;
		while (stack_compare != NULL)
		{
			if(*(int*)looping_pointer->content > *(int*)stack_compare->content)
				lower_numbers_counter++;
			stack_compare = stack_compare->next;
		}
		looping_pointer->index = lower_numbers_counter;
		looping_pointer = looping_pointer->next;
	}
	free(stack_compare);
	return(stack);
}

// a_b->stack_a->index & bit_mask = Transférer pairs dans stack b (last bit 0)
void	sort_above_five(t_2stacks *a_b, int *ops_counter, int *arr_size,
		int highest_nb)
{
	int	i;
	int	bit_mask;

	bit_mask = 1;
	while (true)
	{
		i = 0;
		while ((a_b->stack_a != NULL) && (i < *arr_size))
		{
			if (a_b->stack_a->index > highest_nb)
				highest_nb = a_b->stack_a->index;
			if (!(a_b->stack_a->index & bit_mask))
				push_b(a_b, ops_counter);
			else
				rotate_a(a_b, ops_counter);
			i++;
		}
		while (a_b->stack_b != NULL)
			push_a(a_b, ops_counter);
		bit_mask *= 2;
		if (bit_mask > highest_nb)
			break ;
	}
	return ;
}
