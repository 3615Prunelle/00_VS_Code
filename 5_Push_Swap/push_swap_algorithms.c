/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:05:12 by sophie            #+#    #+#             */
/*   Updated: 2025/08/08 13:07:49 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Without highst_nb_idx==2 (numbers sorted) issues when called by sort_four
void	sort_three(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
		int *ops_counter)
{
	if (lowst_nb_idx == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
		swap_a(a_b, ops_counter);
		// if (highst_nb_idx == 2)
		if (highest_nb_stack_index(a_b->stack_a) == 2)
			return ;
		reverse_rotate_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 1)
	{
		if (highst_nb_idx == 2)
			swap_a(a_b, ops_counter);
		else
			rotate_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 2)
	{
		if (highst_nb_idx == 0)
		{
			swap_a(a_b, ops_counter);
			reverse_rotate_a(a_b, ops_counter);
		}
		else
			reverse_rotate_a(a_b, ops_counter);
	}
}

// If lowst_nb_idx position 0, only last push b necessary
// push_b = mettre smallest dans stack b et trier le reste avec sort_three
// updater lowest car un nombre en moins, va fausser résultats de sort_three
void	sort_four(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
		int *ops_counter)
{
	int	update_lowest;
	int	update_highest;

	if (lowst_nb_idx == 1)
	{
		swap_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 2)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 3)
	{
		reverse_rotate_a(a_b, ops_counter);
	}
	push_b(a_b, ops_counter);
	update_lowest = lowest_number_stack_index(a_b->stack_a);
	update_highest = highest_nb_stack_index(a_b->stack_a);
	sort_three(update_lowest, update_highest, a_b, ops_counter);
	push_a(a_b, ops_counter);
}

// if lowst_nb_idx position 0, only last push b necessary
void	sort_five(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
		int *ops_counter)
{
	int	update_lowest;
	int	update_highest;

	if (lowst_nb_idx == 1)
		swap_a(a_b, ops_counter);
	if (lowst_nb_idx == 2)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 3)
	{
		reverse_rotate_a(a_b, ops_counter);
		reverse_rotate_a(a_b, ops_counter);
	}
	if (lowst_nb_idx == 4)
		reverse_rotate_a(a_b, ops_counter);
	push_b(a_b, ops_counter);
	update_lowest = lowest_number_stack_index(a_b->stack_a);
	update_highest = highest_nb_stack_index(a_b->stack_a);
	sort_four(update_lowest, update_highest, a_b, ops_counter);
	push_a(a_b, ops_counter);
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
