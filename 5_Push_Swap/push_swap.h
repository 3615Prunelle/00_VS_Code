// ⚪ Name of new library defined here (so we can use #include "current_project.h" header)
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// Pour tester une loop si on a pas encore de condition de sortie, mettre while (true) en condition et mettre un break à la fin

// ⚪ #define
# define ERROR_MESSSAGE_01	"Error\nNo args (or not enough) have been provided\n"
# define ERROR_MESSSAGE_02	"Error\nInvalid characters have been found - Try again !\n"
# define ERROR_MESSSAGE_03	"Error\nAt least one number exceeds the int size\n"
# define ERROR_MESSSAGE_04	"Error\nDuplicated number(s), edit and try again !\n"
# define ERROR_MESSSAGE_05	"Nothing to do here - Numbers are already sorted\n"
# define ERROR_MESSSAGE_06	"Error\nSomething went wront with Her Majesty Malloc\n"
# define ERROR_MESSSAGE_07	"Error\n TBD \n"

# define	STACK_A			a_and_b->stack_a
# define	STACK_B			a_and_b->stack_b
# define	STACK_A_CONTENT	*((int*)(a_and_b->stack_a->content))
# define	STACK_B_CONTENT	a_and_b->stack_b->content
# define	STACK_A_NEXT	a_and_b->stack_a->next
# define	STACK_B_NEXT	a_and_b->stack_b->next
# define	STACK_A_INDEX	a_and_b->stack_a->index

# define	SWAP_A		swap_a(a_and_b, ops_counter)
# define	SWAP_B 		swap_b(a_and_b, ops_counter)
# define	SWAP_AB		swap_a_and_b(a_and_b, ops_counter)
# define	PUSH_A		push_a(a_and_b, ops_counter)
# define	PUSH_B		push_b(a_and_b, ops_counter)
# define	ROT_A		rotate_a(a_and_b, ops_counter)
# define	ROT_B		rotate_b(a_and_b, ops_counter)
# define	ROT_AB		rotate_a_and_b(a_and_b, ops_counter)
# define	REVROT_A	reverse_rotate_a(a_and_b, ops_counter)
# define	REVROT_B	reverse_rotate_b(a_and_b, ops_counter)
# define	REVROT_AB	reverse_rotate_a_and_b(a_and_b, ops_counter)

// ⚪ #include (don't forget to put #include "current_project.h" in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
//# include <string.h>
//# include <errno.h> ft_printf("Test errno : [%s]\n", strerror(errno));

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json ou makefile
#include <libft.h>
#include <ft_printf.h>

// ⚪ Structs
//typedef struct s_list	linked_node;			// Alias for struct s_list to make the code more understandable
typedef struct	linked_node
{
	void					*content;
	int						index;
	struct linked_node	*next;
}linked_node;

typedef struct	two_stacks
{
	linked_node	*stack_a;
	linked_node	*stack_b;
}				two_stacks;

// ⚪ Input Management & Check - Functions signatures
int				*two_argv(char *string_input, int *numbers_array, int *array_size);
int				*above_two_argv(char **strings_input, int argc, int *numbers_array, int *array_size);
void			check_array(int *numbers_array, int array_size);
bool			is_numerical_only(char *s);
int				count_numbers(char *s);
int				*string_to_int_array(char *s, int *numbers_array);
int				ft_atol(char *s);
bool			is_number_repeat(int *numbers_array, int array_size);
bool			is_sorted(int *numbers_array, int array_size);
int				ex_smallest_number(int *numbers_array, two_stacks *a_and_b);
int				lowest_number_stack_index(linked_node *stack);
int				highest_number_stack_index(linked_node *stack);

// ⚪ Test functions
void			print_sorted_stack(linked_node *stack);
char			*view_stack(linked_node *stack);

// ⚪ Helpers
linked_node		*create_list(linked_node *stack, int *numbers_array, int array_size);
void			struct_config(int *numbers_array, int array_size);
two_stacks 		*algorithm_selection(two_stacks *a_and_b, int *array_size, int *ops_counter, int *numbers_array);
int				*list_to_array(int *new_array, linked_node *stack);
linked_node		*add_index(int *numbers_array, int array_size, linked_node *stack);

// ⚪ Lst functions
linked_node		*new_node(void *content);
linked_node		*find_last_node(linked_node *lst);
void			add_node_up(linked_node **lst, linked_node *new);
void			add_node_down(linked_node **lst, linked_node *new);
int				count_nodes(linked_node *lst);

// ⚪ Algorithms
void			sort_three(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter);
void			sort_four(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter);
void			sort_five(int lowest_number_index, int highest_number_index, two_stacks *a_and_b, int *ops_counter);
void			sort_above_five(two_stacks *a_and_b, int *ops_counter);

// ⚪ Operations
two_stacks		*swap_a(two_stacks *a_and_b, int *ops_counter);
two_stacks		*swap_b(two_stacks	*a_and_b, int *ops_counter);
two_stacks		*swap_a_and_b(two_stacks *a_and_b, int *ops_counter);
two_stacks		*push_a(two_stacks *a_and_b, int *ops_counter);
two_stacks		*push_b(two_stacks *a_and_b, int *ops_counter);
two_stacks		*rotate_a(two_stacks *a_and_b, int *ops_counter);
two_stacks		*rotate_b(two_stacks *a_and_b, int *ops_counter);
two_stacks		*rotate_a_and_b(two_stacks *a_and_b, int *ops_counter);
two_stacks		*reverse_rotate_a(two_stacks *a_and_b, int *ops_counter);
two_stacks		*reverse_rotate_b(two_stacks *a_and_b, int *ops_counter);
two_stacks		*reverse_rotate_a_and_b(two_stacks *a_and_b, int *ops_counter);

// ⚪ Clean up functions
void			clean_early_exit(char *message, int *numbers_array, bool exit_wanted);
void			clean_exit(char *message, two_stacks *a_and_b, bool exit_wanted);
#endif
