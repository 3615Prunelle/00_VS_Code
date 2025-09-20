#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ‼️ Global variables are forbidden

// ⚪ #define
# define ERROR_MESSSAGE_01	"Error\n"
# define AVAILABLE 1
# define TAKEN 0
# define EATING 44
# define THINKING 66
# define SLEEPIING 88

// ‼️ Si je mets des paths, mettre le chemin RELATIF depuis le dossier d'ou sera lancée la commande. Ce chemin est différent selon si je suis :
// - Sur mon PC perso
// - Sur l'ordi du campus
// ET selon si je :
// - Fais 'make' depuis le dossier du projet (path from projet folder)
// - Compile via VSCode (path from workspaceFolder)

// ⚪ #include
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>

// ⚪ Structs
typedef struct	all_data
{
	pthread_t	*all_yakuzas;
	int			amount_of_yakuzas;
	int			**amount_of_chopsticks_available;
	int			time_to_die;									// In milliseconds - Is it the right kind of variable ?
	int			time_to_eat;									// Same question as above
	int			time_to_sleep;									// Same question as above
	int			number_of_times_each_philosopher_must_eat;		// Optional argument
}				all_data;

typedef struct	one_bro
{
	int		position;
	int		current_state;
	bool	has_chopstick_right;
	bool	has_chopstick_left;
}				one_bro;

// ⚪ Functions signatures - Part 1

// ⚪ Functions signatures - Part 2

// ⚪ Clean up functions

// ⚪ Test functions

#endif
