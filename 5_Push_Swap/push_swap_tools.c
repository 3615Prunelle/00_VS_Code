/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:03:26 by sophie            #+#    #+#             */
/*   Updated: 2025/08/08 12:32:29 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	lowest_number_stack_index(t_node *stack)
{
	int	i;
	int	lowest_number;
	int	lowst_nb_idx;

	i = 0;
	lowest_number = INT_MAX;
	while (stack != NULL)
	{
		if (*(int *)(stack->content) < lowest_number)
		{
			lowest_number = *(int *)(stack->content);
			lowst_nb_idx = i;
		}
		i++;
		stack = stack->next;
	}
	return (lowst_nb_idx);
}

int	highest_nb_stack_index(t_node *stack)
{
	int	i;
	int	highest_nb;
	int	highst_nb_idx;

	i = 0;
	highest_nb = INT_MIN;
	while (stack != NULL)
	{
		if (*(int *)(stack->content) > highest_nb)
		{
			highest_nb = *(int *)(stack->content);
			highst_nb_idx = i;
		}
		i++;
		stack = stack->next;
	}
	return (highst_nb_idx);
}

// Change int for int* in struct if errors
t_node	*add_index(int *numbers_arr, int *arr_size, t_node *stack)
{
	int		i;
	int		j;
	int		lower_numbers_counter;
	t_node	*stack_copy;

	i = 0;
	lower_numbers_counter = 0;
	stack_copy = stack;
	while (i < *arr_size)
	{
		j = 0;
		lower_numbers_counter = 0;
		while (j < *arr_size)
		{
			if (numbers_arr[i] > numbers_arr[j])
			{
				lower_numbers_counter++;
			}
			j++;
		}
		stack_copy->index = lower_numbers_counter;
		stack_copy = stack_copy->next;
		i++;
	}
	return (stack);
}

// NULL Pour éviter erreurs dans Valgrind
// comment print_sorted_stack when done
// Avant de passer dans clean_exit, stack b == NULL, et on ne l'a pas malloc'é
// Lignes à rajouter avant clean_exit si need tests
	// print_sorted_stack(a_b->stack_a);
	// ft_printf("Operations counter : %i\n", ops_counter);
	// ft_printf("Amount of numbers : %i\n", *arr_size);
void	struct_config(int *numbers_arr, int *arr_size)
{
	int			ops_counter;
	t_2stacks	*a_b;

	ops_counter = 0;
	a_b = malloc(sizeof(t_2stacks));
	a_b->stack_a = NULL;
	a_b->stack_b = NULL;
	if (!a_b)
		clean_early_exit(ERROR_MSG, numbers_arr);
		// clean_early_exit(ERROR_MSG_06, numbers_arr);
	a_b->stack_a = create_stack(a_b->stack_a, numbers_arr, arr_size);
	a_b = algorithm_selection(a_b, arr_size, &ops_counter, numbers_arr);
	free_nodes(a_b);
	free(numbers_arr);
	return ;
}

// highest_nb donné en param pour gratter 2 lignes dans les fonctions appelées
t_2stacks	*algorithm_selection(t_2stacks *a_b, int *arr_size,
		int *ops_counter, int *numbers_arr)
{
	int	lowst_nb_idx;
	int	highst_nb_idx;
	int	highest_nb;

	lowst_nb_idx = lowest_number_stack_index(a_b->stack_a);
	highst_nb_idx = highest_nb_stack_index(a_b->stack_a);
	highest_nb = INT_MIN;
	if (*arr_size == 2)
		swap_a(a_b, ops_counter);
	if (*arr_size == 3)
		sort_three(lowst_nb_idx, highst_nb_idx, a_b, ops_counter);
	if (*arr_size == 4)
		sort_four(lowst_nb_idx, highst_nb_idx, a_b, ops_counter);
	if (*arr_size == 5)
		sort_five(lowst_nb_idx, highst_nb_idx, a_b, ops_counter);
	if (*arr_size > 5)
	{
		add_index(numbers_arr, arr_size, a_b->stack_a);
		sort_above_five(a_b, ops_counter, arr_size, highest_nb);
	}
	return (a_b);
}
