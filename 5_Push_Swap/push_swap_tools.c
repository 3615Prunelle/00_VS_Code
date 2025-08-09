/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:03:26 by sophie            #+#    #+#             */
/*   Updated: 2025/08/09 09:55:46 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Change int for int* in struct if errors
t_node	*add_index_above5(int *numbers_arr, int *arr_size, t_node *stack)
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
	int	highest_nb;

	add_update_index(a_b->stack_a);	// change name to add/update under 5

	highest_nb = INT_MIN;
	if (*arr_size == 2)
		swap_a(a_b, ops_counter);
	if (*arr_size == 3)
		sort_three(a_b, ops_counter);
	if (*arr_size == 4)
		sort_four(a_b, ops_counter);
	if (*arr_size == 5)
		sort_five(a_b, ops_counter);
	if (*arr_size > 5)
	{
		add_index_above5(numbers_arr, arr_size, a_b->stack_a);
		sort_above_five(a_b, ops_counter, arr_size, highest_nb);
	}
	return (a_b);
}
