// ⚪ Name of new library defined here (so we can use #include "current_project.h" header)
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// ⚪ #define
# define ARR_SIZE 8

// ⚪ #include (don't forget to put #include "current_project.h" in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
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

// ⚪ Pre launch check functions

// ⚪ Operations

linked_number	*swap(linked_number *stack);
two_stacks		*swap_a_and_b(linked_number *stack_a, linked_number *stack_b);
void			push_a(linked_number *stack_a, linked_number *stack_b);

// ⚪ Helpers
linked_number	*create_list(int array[]);

// ⚪ Test
void			verif(char *fonction, linked_number *stack);

// ⚪ Clean up functions

#endif
