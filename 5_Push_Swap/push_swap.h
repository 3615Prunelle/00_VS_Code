// ⚪ Name of new library defined here (so we can use #include "current_project.h" header)
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// ⚪ #define
# define ERROR_MESSSAGE_01	"Error\nNo args have been provided\n"
# define ERROR_MESSSAGE_02	"Error\nInvalid characters have been found - Try again !\n"
# define ERROR_MESSSAGE_03	"Error\nAt least one number exceeds the int size\n"
# define ERROR_MESSSAGE_04	"Error\nDuplicated number, edit and try again !\n"
# define ERROR_MESSSAGE_05	"Nothing to do here - Numbers are already sorted\n"
# define ERROR_MESSSAGE_06	"Error\nSomething went wront with Her Majesty Malloc\n"
# define ERROR_MESSSAGE_07	"Error\n TBD \n"

# define	STACK_A			a_and_b->stack_a
# define	STACK_B			a_and_b->stack_b
# define	STACK_A_CONTENT	a_and_b->stack_a->content
# define	STACK_B_CONTENT	a_and_b->stack_b->content
# define	STACK_A_NEXT	a_and_b->stack_a->next
# define	STACK_B_NEXT	a_and_b->stack_b->next

// ⚪ #include (don't forget to put #include "current_project.h" in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
//# include <string.h>
//# include <errno.h> ft_printf("Test errno : [%s]\n", strerror(errno));

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ ‼️ ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json
#include "../1_Libft/libft.h"
#include "../2_ft_printf/ft_printf.h"

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
long int		*string_to_int_array(int count, char *s, long int *numbers_array);
long int		ft_atol(char *s);
bool			is_number_repeat(long int *numbers_array, int array_size);
bool			is_sorted(long int *numbers_array, int array_size);

// ⚪ Test functions
void			verif(char *fonction, two_stacks *a_and_b);

// ⚪ Helpers
linked_number	*create_list(linked_number *stack, long int array[], int array_size);
void			algorithm_selection(long int numbers_array[], int array_size);

// ⚪ Operations
two_stacks		*swap_a(two_stacks *a_and_b);
two_stacks		*swap_b(two_stacks	*a_and_b);
two_stacks		*swap_a_and_b(two_stacks *a_and_b);
two_stacks		*push_a(two_stacks *a_and_b);
two_stacks		*push_b(two_stacks *a_and_b);
two_stacks		*rotate_a(two_stacks *a_and_b);
two_stacks		*rotate_b(two_stacks *a_and_b);
two_stacks		*rotate_a_and_b(two_stacks *a_and_b);
two_stacks		*reverse_rotate_a(two_stacks *a_and_b);
two_stacks		*reverse_rotate_b(two_stacks *a_and_b);
two_stacks		*reverse_rotate_a_and_b(two_stacks *a_and_b);

// ⚪ Clean up functions
void			clean_early_exit(char *message, bool exit_wanted);
void			clean_exit(char *message, two_stacks *a_and_b, bool exit_wanted);
#endif
