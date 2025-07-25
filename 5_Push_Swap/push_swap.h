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
# define	STACK_A_CONTENT	*((int *)(a_and_b->stack_a->content))
# define	STACK_B_CONTENT	a_and_b->stack_b->content
# define	STACK_A_NEXT	a_and_b->stack_a->next
# define	STACK_B_NEXT	a_and_b->stack_b->next

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
typedef struct s_list	linked_number;			// Alias for struct s_list to make the code more understandable

typedef struct	two_stacks
{
	linked_number	*stack_a;
	linked_number	*stack_b;
}				two_stacks;

// ⚪ Input Management & Check
bool			is_numerical_only(char *s);
int				count_numbers(char *s);
int				*string_to_int_array(char *s, long int *numbers_array);
long int		ft_atol(char *s);
bool			is_number_repeat(long int *numbers_array, int array_size);
bool			is_sorted(long int *numbers_array, int array_size);
int				ex_smallest_number(long int *numbers_array, two_stacks *a_and_b);
int				lowest_number_stack_index(linked_number *stack);
int				highest_number_stack_index(linked_number *stack);

// ⚪ Test functions
void			verif(char *fonction, two_stacks *a_and_b);
void			ex_print_sorted_stack(two_stacks *a_and_b);
void			print_sorted_stack(linked_number *stack);
char			*view_stack(linked_number *stack);

// ⚪ Helpers
linked_number	*create_list(linked_number *stack, long int *numbers_array, int array_size);
void			algorithm_selection(long int *numbers_array, int array_size);
int				*list_to_array(int *new_array, linked_number *stack);

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
void			clean_early_exit(char *message, long int *numbers_array, bool exit_wanted);
void			clean_exit(char *message, two_stacks *a_and_b, bool exit_wanted);
#endif
