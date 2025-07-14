#include "so_long.h"

// -------- ⬇️ Draw everything in correct order ✅
void		display_map(game *my_game)
{
	my_game->ground_image = path_to_image(my_game, my_game->window, PATH_GROUND);

	int column;
	int line = 0;

	while (line < my_game->max_lines)
	{
		column = 0;
		while (column < my_game->max_columns)
		{
			display_image(my_game, my_game->ground_image, column, line);
			column++;
		}
		line++;
	}

	my_game->wall_image = path_to_image(my_game, my_game->window, PATH_WALL);

	my_game->collectible_image = path_to_image(my_game, my_game->window, PATH_COLLECTIBLE);

	my_game->escape_image = path_to_image(my_game, my_game->window, PATH_ESCAPE);

	line = 0;
	while (line < my_game->max_lines)
	{
		column = 0;
		while (my_game->content[line][column] != '\n')
		{
			if (my_game->content[line][column] == '1')
				display_image(my_game, my_game->wall_image, column, line);
			else if (my_game->content[line][column] == 'C')
				display_image(my_game, my_game->collectible_image, column, line);
			else if (my_game->content[line][column] == 'E')
				display_image(my_game, my_game->escape_image, column, line);
			else if (my_game->content[line][column] == 'P')
				display_image(my_game, my_game->player_image, column, line);
			column++;
		}
		line++;
	}
}

void		display_image(game *my_game, mlx_image_t *image, int colonne, int ligne)
{
	if (mlx_image_to_window(my_game->window, image, colonne*TILE_SIZE, ligne*TILE_SIZE) == -1)	// Affiche une instance de l'image. Peut être utilisé à chaque fois qu'on veut display l'image à un endroit différent
	{
		ft_printf(ERROR_MESSSAGE_11);
		clean_and_exit(my_game);
	}
}

// -------- ⬇️ Centraliser le process de chargement de textures ✅ + Conversion en image ✅ + Error handling ✅ + Deal with memory ‼️
mlx_image_t	*path_to_image(game *my_game, mlx_t *game_window, char *path)
{
	// ------------------------------ Set up Texture buffer (texture = Image pas encore affichée, mais prête à l’être) ✅Ⓜ️🆓
	mlx_texture_t *texture;
	if (!(texture = mlx_load_png(path)))	// Access the image data - 🆓 MLX Malloc (free below in the same function)
	{
		//ft_printf("Error in loading PNG file\n"); // No need to put error message because mlx_load_png does it
		clean_and_exit(my_game);
	}
// -------------------------------------------------------------------------- Convert the texture to a diplayable image ✅
	mlx_image_t *image;													// Set up image buffer - Note : mlx_image_t doit etre toujours un ptr
	if (!(image = mlx_texture_to_image(game_window, texture)))			// Create a displayable image from texture data - MLX MALLOC DONE HERE 🆓
	{
		mlx_delete_texture(texture);
		//ft_printf("Error in allocating image buffer\n"); // No need to put error message because mlx_texture_to_image does it ?? To double check
		clean_and_exit(my_game);
	}
	mlx_delete_texture(texture);			// ✅ Free - No need to set to null because the variable is local (= no dangling pointer)
	return(image);
}

void		key_actions(mlx_key_data_t keydata, void *param) // Je lui ai passé l'adresse de my_game dans la fonction appelante car je dois respecter le "void param" que mlx_key_hook me demande
{
	game	*my_game;	// Structure (declared in .h) pour que cette fonction accepte (au moins) 2 parametres au lieu d'un
	my_game = param;

	int		move;
	move = 0;

	int		collectibles_amount;											// A chaque touche pressée, on check le nombre de collectibles restant
	collectibles_amount = get_collectibles_left(*my_game);			// bool parameter probably not useful anymore, run tests & remove it

	if (!my_game || !my_game->player_image || my_game->player_image->count < 1)
		return;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)	// Exit on ESC key
	{
		//mlx_close_window(my_game->window);							// previous option - maybe not necessary anymore
		ft_printf(OK_MESSSAGE_03);
		clean_and_exit(my_game);
	}

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)	// Quelle touche + Est-elle pressée ?
	{
		move = RIGHT;								// Vérif si move possible + MAJ des coordonnées du joueur si autorisé
	}

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		move = LEFT;
	}

	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		move = UP;
	}

	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		move = DOWN;
	}

	if (!move)
		return;

	player_move(*my_game, move);			// Cette fonction ne s'occupe que du déplacement du joueur dans le fonctionnement interne du jeu

	tile updated_player_position = get_tile_position(*my_game, PLAYER);
	my_game->player_image->instances[0].x = updated_player_position.column * TILE_SIZE;		// Déplacement de l'image en prenant en compte l'échelle du jeu
	my_game->player_image->instances[0].y = updated_player_position.line * TILE_SIZE;		// 1 case (dans représentation non graphique) = 72 pixels (rep visuelle)

// ------------------------------------------------------------------------------------------------ If on collectible : delete collectible instance ✅
	size_t	index = 0;
	while (index < my_game->collectible_image->count)
	{
		if (my_game->player_image->instances[0].x == my_game->collectible_image->instances[index].x
			&& my_game->player_image->instances[0].y == my_game->collectible_image->instances[index].y)
		{
			my_game->collectible_image->instances[index].enabled = false;
		}
		index++;
	}
// ------------------------------------------------------------------------------------------------- If on escape + collectibles fetched : exit game ✅
	if (collectibles_amount == 0)
	{
		if (my_game->player_image->instances[0].x == my_game->escape_image->instances[0].x
			&& my_game->player_image->instances[0].y == my_game->escape_image->instances[0].y)
		{
			my_game->escape_image->instances[0].enabled = false;
			mlx_close_window(my_game->window);
		}
		index++;
	}
	//print_map_fun(*my_game);			// Only for testing purposes
}


void		bonus_counter(game my_game, int step_counter)
{
	static mlx_image_t	*bonus_string1;
	static mlx_image_t	*bonus_string2;

	if (bonus_string1)
		mlx_delete_image(my_game.window, bonus_string1);
	if (bonus_string2)
		mlx_delete_image(my_game.window, bonus_string2);

	char *string_to_display;
	string_to_display = "Step counter";
	bonus_string1 = mlx_put_string(my_game.window, string_to_display, 50, 15);

	char *number_to_diplay;
	number_to_diplay = ft_itoa(step_counter);					// 🆓 Malloc
	bonus_string2 = mlx_put_string(my_game.window, number_to_diplay, 100, 35);
	free(number_to_diplay);										// ✅ Free
}
