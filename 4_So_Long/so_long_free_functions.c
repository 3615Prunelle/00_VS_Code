#include "so_long.h"

void	simple_print_exit(char *s)
{
	ft_printf("Error : [%s]\n", s);
	exit(1);
}

// char **line etant l'adresse d'un pointeur, char *line est donc un pointeur, qu'on doit free puis remettre a zero
// close(*fd); Dereference le pointeur vers fd pour le fermer - Fermer un fd est important pour eviter les fd leaks
// A la fin, on force GNL avec une valeur neg pour libérer son static buffer
void	free_gnl_return_and_exit(char *error_message, char **line, int *fd)
{
	ft_printf("%s\n", error_message);
	free(*line);
	*line = NULL;
	close(*fd);
	get_next_line(-1);
	exit(1);
}

// Free toutes les lignes de content (avant fonctions MLX42 ou après leur clean up)
void	free_logic_part(char *message, s_game *any_game)
{
	ft_printf("%s", message);
	while (any_game->max_lines > 0)
	{
		free(any_game->content[any_game->max_lines - 1]);
		any_game->max_lines--;
	}
	if (any_game->content)
	{
		free(any_game->content);
	}
}

// Free everything MLX42 related when exit game
void	clean_and_exit(void *param)
{
	s_game	*game;

	game = param;
	if (!game)
		return ;
	if (game->ground_image)
		mlx_delete_image(WINDOW, game->ground_image);
	if (WALL_IMG)
		mlx_delete_image(WINDOW, WALL_IMG);
	if (PLAYER_IMG)
		mlx_delete_image(WINDOW, PLAYER_IMG);
	if (COLLECTIBLE_IMG)
		mlx_delete_image(WINDOW, COLLECTIBLE_IMG);
	if (ESCAPE_IMG)
		mlx_delete_image(WINDOW, ESCAPE_IMG);
	if (game->bonus_string1)
		mlx_delete_image(WINDOW, game->bonus_string1);
	if (game->bonus_string2)
		mlx_delete_image(WINDOW, game->bonus_string2);
	if (WINDOW)
		mlx_terminate(WINDOW);
	free_logic_part(OK_MESSSAGE_05, game);
	ft_printf("... Something to add, Queen Strerror ? : [%s]\n\n",
		strerror(errno));
	exit(1);
}
