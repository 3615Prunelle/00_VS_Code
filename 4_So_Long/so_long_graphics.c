#include "so_long.h"

// Draw everything in correct order (ground then ICE then P) to avoid conflicts with depth
void	display_map(s_game *game)
{
	int	column;
	int	line;

	game->ground_image = path_to_image(game, WINDOW, PATH_GROUND);
	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (column < game->max_columns)
		{
			display_image(game, game->ground_image, column, line);
			column++;
		}
		line++;
	}
	WALL_IMG = path_to_image(game, WINDOW, PATH_WALL);
	COLLECTIBLE_IMG = path_to_image(game, WINDOW, PATH_COLLECTIBLE);
	ESCAPE_IMG = path_to_image(game, WINDOW, PATH_ESCAPE);
	add_1CE_images(game);
	add_P_image(game);
}

void	add_1CE_images(s_game *game)
{
	int	line;
	int	column;

	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (game->content[line][column] != '\n')
		{
			if (game->content[line][column] == '1')
				display_image(game, WALL_IMG, column, line);
			else if (game->content[line][column] == 'C')
				display_image(game, COLLECTIBLE_IMG, column, line);
			else if (game->content[line][column] == 'E')
				display_image(game, ESCAPE_IMG, column, line);
			column++;
		}
		line++;
	}
}

void	add_P_image(s_game *game)
{
	int	line;
	int	column;

	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (game->content[line][column] != '\n')
		{
			if (game->content[line][column] == 'P')
				display_image(game, PLAYER_IMG, column, line);
			column++;
		}
		line++;
	}
}

// Affiche une instance de l'image. Peut être utilisé à chaque fois qu'on veut display l'image à un endroit différent
void	display_image(s_game *game, mlx_image_t *image, int column, int line)
{
	if (mlx_image_to_window(WINDOW, image, column * TILE_SIZE, line
			* TILE_SIZE) == -1)
	{
		ft_printf(ERROR_MESSSAGE_10);
		clean_and_exit(game);
	}
}

// Centraliser le process de chargement de textures + Conversion en image + Error handling + Deal with memory
// Step 1 : Set up Texture buffer (texture = Image pas encore affichée, mais prête à l’être)
// mlx_load_png(path) displays error message if fail, no need to do it
// Step 2 : Convert the texture to a diplayable image (= set up image buffer)
// Create a displayable image from texture data
// Free the texture as we don't need it anymore
mlx_image_t	*path_to_image(s_game *game, mlx_t *game_window, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	// ------------------------------  ✅Ⓜ️🆓
	if (!(texture = mlx_load_png(path)))
	{
		clean_and_exit(game);
	}
	if (!(image = mlx_texture_to_image(game_window, texture)))
	{
		mlx_delete_texture(texture);
		clean_and_exit(game);
	}
	mlx_delete_texture(texture);
	return (image);
}

// Je passe l'adresse de game dans la fonction appelante car je dois respecter le "void param" que mlx_key_hook me demande
// Variable move est utilisée dans la fonction target_position
// A chaque touche pressée, on check le nombre de collectibles restants
void	key_actions(mlx_key_data_t keydata, void *param)
{
	s_game	*game;
	int		move;

	game = param;
	move = 0;
	if (!game || !PLAYER_IMG || PLAYER_IMG->count < 1)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf(OK_MESSSAGE_03);
		clean_and_exit(game);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move = RIGHT;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move = LEFT;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move = UP;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move = DOWN;
	if (!move)
		return ;
	move_player_logic(*game, move);
	move_player_graphic(game);
	delete_collectible_instance(game);
}

void	bonus_counter(s_game game, int step_counter)
{
	static mlx_image_t	*bonus_string1;
	static mlx_image_t	*bonus_string2;
	char				*string_to_display;
	char				*number_to_diplay;

	if (bonus_string1)
		mlx_delete_image(game.window, bonus_string1);
	if (bonus_string2)
		mlx_delete_image(game.window, bonus_string2);
	string_to_display = "Step counter";
	bonus_string1 = mlx_put_string(game.window, string_to_display, 50, 15);
	number_to_diplay = ft_itoa(step_counter);
	bonus_string2 = mlx_put_string(game.window, number_to_diplay, 100, 35);
	free(number_to_diplay);
}
