#include "so_long.h"

void	free_gnl_stuff(char *error_message, char **line, int *fd)
{
	ft_printf("%s\n", error_message);

	free(*line);			// char **line etant l'adresse d'un pointeur, char *line est donc un pointeur, qu'on free [...]
	*line = NULL;			// [...] puis remet a zero
	close(*fd);				// Dereference le pointeur vers fd pour le fermer - Fermer un fd est important pour eviter les fd leaks
	get_next_line(-1);		// Force GNL to free its static buffer

	exit(1);				// exit sort du programme / return sort de la fonction
}

// -------------------------------------------------------------------------------------------- Edit & use when things get spicy ‼️
void	free_game(char *error_message, game *any_game)			// Pour free toutes les lignes de content (rien d'autre à free qui ne soit pas dans MLX42)
{
	ft_printf("%s\n", error_message);

	while (any_game->max_lines > 0)
	{
		free(any_game->content[any_game->max_lines-1]);
		any_game->max_lines--;
	}
	free(any_game->content);

	//exit(1); // Maybe not necessary because this function is also alsed when no error occurs
}

// -------------------------------------------------------------------------------- Free everything MLX42 related when exit game ‼
void	ft_free_exit(all_mallocs *free_this)
	{
		if (!free_this)
			return;
// ‼️ If anything else is allocated : Add it here
// ‼️ If anything was allocated by me (rather than MLX) : Use free (rather than a MLX delete function)

		if(free_this->player_image)
			mlx_delete_image(free_this->window, free_this->player_image);

	// add free(my_game) when previous code is connected to the MLX42 part ‼️

		if(free_this->window)
			mlx_terminate(free_this->window);							// Free game_window

		free(free_this);
		free_this = NULL;
	}
// --------------------------------------------------------------------------- Quit in a clean way when clic on cross. MEM LEAKS ‼️
void	free_before_exit(void *param) // model = mlx_closefunc
{
	all_mallocs	*free_this;
	free_this = param;

	ft_printf("Brutal exit\n");

	//ft_free_exit(free_this);			// Segfault if kept
}

void	clean_window_exit(const char *error_message, mlx_t *game_window)
{
	ft_printf("%s\n", error_message);
	mlx_terminate(game_window);				// Destroy and clean up all images and mlx resources ‼️ Doesn't exit
	exit(1);
}

void	clean_game_exit(char *error_message, game *my_game)
{
	ft_printf("%s\n", error_message);
	// free(game) somehow
	exit(1);									// exit sort du programme / return sort de la fonction
}
