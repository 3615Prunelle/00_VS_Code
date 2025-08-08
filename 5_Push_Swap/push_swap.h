/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:47:23 by sophie            #+#    #+#             */
/*   Updated: 2025/08/08 13:29:15 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// ⚪ #define
# define ERROR_MSG "Error\n"
// # define ERROR_MSG_01 "Error\nNot enough args have been provided\n"
// # define ERROR_MSG_02 "Error\nInvalid characters have been found - Try again\n"
// # define ERROR_MSG_03 "Error\nAt least one number exceeds the int size\n"
// # define ERROR_MSG_04 "Error\nDuplicated number(s), edit and try again !\n"
// # define ERROR_MSG_05 "Nothing to do here - Numbers are already sorted\n"
// # define ERROR_MSG_06 "Error\nSomething went wront with Her Majesty Malloc\n"

// ⚪ #include
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ⚪ #include from other 42 projects
# include <ft_printf.h>
# include <libft.h>

// ⚪ Structs
typedef struct node
{
	void		*content;
	int			index;
	struct node	*next;
}				t_node;

typedef struct stacks
{
	t_node		*stack_a;
	t_node		*stack_b;
}				t_2stacks;

// ⚪ Functions signatures - Pre_Stack Creation (Input Management & Check)
int				*two_argv(char *input, int *numbers_arr, int *arr_size);
int				*above_two_argv(char **inputs, int argc, int *numbers_arr,
					int *arr_size);
int				ft_atol(char *s);
int				count_numbers(char *s);
int				*string_to_int_array(char *s, int *numbers_arr);
bool			is_numerical_only(char *s);
void			check_array(int *numbers_arr, int *arr_size);
bool			is_number_repeat(int *numbers_arr, int arr_size);
bool			is_sorted(int *numbers_arr, int arr_size);
int				lowest_number_stack_index(t_node *stack);
int				highest_nb_stack_index(t_node *stack);

// ⚪ Post Stack Creation
t_node			*create_stack(t_node *stack, int *numbers_arr, int *arr_size);
void			struct_config(int *numbers_arr, int *arr_size);
t_2stacks		*algorithm_selection(t_2stacks *a_b, int *arr_size,
					int *ops_counter, int *numbers_arr);
t_node			*add_index(int *numbers_arr, int *arr_size, t_node *stack);

// ⚪ Lst functions
t_node			*new_node(void *content);
t_node			*find_last_node(t_node *lst);
void			add_node_up(t_node **lst, t_node *new);
void			add_node_down(t_node **lst, t_node *new);
int				count_nodes(t_node *lst);

// ⚪ Algorithms
void			sort_three(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
					int *ops_counter);
void			sort_four(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
					int *ops_counter);
void			sort_five(int lowst_nb_idx, int highst_nb_idx, t_2stacks *a_b,
					int *ops_counter);
void			sort_above_five(t_2stacks *a_b, int *ops_counter, int *arr_size,
					int highest_nb);

// ⚪ Operations
t_2stacks		*swap_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*swap_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*swap_a_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*push_a(t_2stacks *a_b, int *ops_counter);
t_2stacks		*push_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*rotate_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*rotate_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*rotate_a_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*reverse_rotate_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*reverse_rotate_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*reverse_rotate_a_b(t_2stacks *a_b, int *ops_counter);

// ⚪ Clean up functions
void			clean_early_exit(char *msg, int *numbers_arr);
void			free_nodes(t_2stacks *a_b);

// ⚪ Test functions
// void			print_sorted_stack(t_node *stack);
#endif
