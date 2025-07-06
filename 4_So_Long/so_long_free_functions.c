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
void	free_game_content_and_exit(char *error_message, game *any_game)			// Pour free toutes les lignes de content (rien d'autre à free qui ne soit pas dans MLX42)
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
void	clean_and_exit(void *param)
{
	ft_printf("Pass in clean_and_exit function\n");

	game *my_game;
	my_game = param;

	if (!my_game)
		return;
// ‼️ If anything else is allocated : Add it here
// ‼️ If anything was allocated by me (rather than MLX) : Use free (rather than a MLX delete function)

	if(my_game->ground_image)
		mlx_delete_image(my_game->window, my_game->ground_image);

	if(my_game->wall_image)
		mlx_delete_image(my_game->window, my_game->wall_image);

	if(my_game->player_image)
		mlx_delete_image(my_game->window, my_game->player_image);

	if(my_game->collectible_image)
		mlx_delete_image(my_game->window, my_game->collectible_image);

	if(my_game->escape_image)
		mlx_delete_image(my_game->window, my_game->escape_image);

	if(my_game->bonus_string1)
		mlx_delete_image(my_game->window, my_game->bonus_string1);

	if(my_game->bonus_string2)
		mlx_delete_image(my_game->window, my_game->bonus_string2);

	if(my_game->window)
		mlx_terminate(my_game->window);												// Free game_window

	free_game_content_and_exit("Game content is theorically free\n", my_game);		// Pour supprimer le game.conten
	// free(my_game);																// Pour supprimer la struct - Maybe not required (double free if commented out)
	my_game = NULL;
	exit(1);									// exit sort du programme / return sort de la fonction
}
