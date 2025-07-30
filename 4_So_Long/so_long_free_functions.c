#include "so_long.h"

void	free_gnl_return_and_exit(char *error_message, char **line, int *fd)
{
	ft_printf("%s\n", error_message);

	free(*line);			// char **line etant l'adresse d'un pointeur, char *line est donc un pointeur, qu'on free [...]
	*line = NULL;			// [...] puis remet a zero
	close(*fd);				// Dereference le pointeur vers fd pour le fermer - Fermer un fd est important pour eviter les fd leaks
	get_next_line(-1);		// Force GNL to free its static buffer

	exit(1);				// exit sort du programme / return sort de la fonction
}
// ---- ⬇️ Free toutes les lignes de content (avant fonctions MLX42 ou après leur clean up)
void	free_game_content(char *message, game *any_game, bool need_exit)
{
	ft_printf("%s\n", message);

	while (any_game->max_lines > 0)
	{
		free(any_game->content[any_game->max_lines-1]);
		any_game->max_lines--;
	}

	if(any_game->content)
	{
		free(any_game->content);			// Libère le tableau de pointeurs
	}

	if(need_exit)
	{
		exit(1);		// Because this function is also called when no error occurs
	}
	ft_printf(OK_MESSSAGE_04);
}

// ---- ⬇️ Free everything MLX42 related when exit game ‼
void	clean_and_exit(void *param)
{
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

	free_game_content(OK_MESSSAGE_05, my_game, false);		// Pour supprimer le game.content

	ft_printf(OK_MESSSAGE_06);
	ft_printf("\nWhat does Queen Strerror have to say ? : [%s]\n", strerror(errno));
	exit(1);
}
