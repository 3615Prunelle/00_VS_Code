#include "so_long.h"

void		display_map(game *my_game)
{
	// ------------------------------------------------------------ Render checklist - Draw everything in correct order ✅
	mlx_image_t	*background_image;						// N'existe que dans cette fonction, à moins de le mettre dans struct
	background_image = path_to_image(my_game->window, "./4_So_Long/ic_Grou.png");

	int column;
	int line = 0;

	while (line < my_game->max_lines)
	{
		column = 0;
		while (column < my_game->max_columns)
		{
			display_image(my_game->window, background_image, column, line);
			column++;
		}
		line++;
	}

	mlx_image_t	*wall_image;
	wall_image = path_to_image(my_game->window, "./4_So_Long/ic_Wall.png");

	my_game->collectible_image = path_to_image(my_game->window, "./4_So_Long/ic_Coll.png");
	// Add image to "stuff to free" + all other images ? Or not necessary anymore ?

	my_game->escape_image = path_to_image(my_game->window, "./4_So_Long/ic_Exit.png");

	line = 0;
	while (line < my_game->max_lines)
	{
		column = 0;
		while (my_game->content[line][column] != '\n')
		{
			if (my_game->content[line][column] == '1')
				display_image(my_game->window, wall_image, column, line);
			else if (my_game->content[line][column] == 'C')
				display_image(my_game->window, my_game->collectible_image, column, line);
			else if (my_game->content[line][column] == 'E')
				display_image(my_game->window, my_game->escape_image, column, line);
			else if (my_game->content[line][column] == 'P')
				display_image(my_game->window, my_game->player_image, column, line);
			column++;
		}
		line++;
	}
}

void		display_image(mlx_t *game_window, mlx_image_t *image, int colonne, int ligne)
{
	if (mlx_image_to_window(game_window, image, colonne*TILE_SIZE, ligne*TILE_SIZE) == -1)	// Affiche une instance de l'image. Peut être utilisé à chaque fois qu'on veut display l'image à un endroit différent
	{
		ft_printf("Erreur lors de l'affichage de l'image\n");
		//ft_free_exit(stuff_to_free);
		exit (1);
	}
}

// ----------------------- Centraliser le process de chargement de textures ✅ + Conversion en image ✅ + Error handling ✅ + Deal with memory ‼️
mlx_image_t	*path_to_image(mlx_t *game_window, char *path)
{
	// ------------------------------ Set up Texture buffer (texture = Image pas encore affichée, mais prête à l’être) ✅Ⓜ️🆓
	mlx_texture_t *texture;
	if (!(texture = mlx_load_png(path)))	// Access the image data - MLX MALLOC DONE HERE ‼️
	{
		clean_window_exit(mlx_strerror(mlx_errno), game_window); // Maybe other stuff to free - Check later if mem leaks
	}

// -------------------------------------------------------------------------- Convert the texture to a diplayable image ✅Ⓜ️🆓
	mlx_image_t *image;															// Set up image buffer - Note : mlx_image_t doit etre toujours un ptr
	if (!(image = mlx_texture_to_image(game_window, texture)))			// Create a displayable image from texture data - MLX MALLOC DONE HERE ‼️
	{
		mlx_delete_texture(texture);
		clean_window_exit("Error in allocating new image buffer\n", game_window);
	}
	//stuff_to_free->image =	image;
	mlx_delete_texture(texture);			// No need to set to null because the variable is local (= no dangling pointer)
	return(image);
}

void		key_actions(mlx_key_data_t keydata, void *param) // Je lui ai passé l'adresse de my_game dans la fonction appelante
{
	game	*my_game;	// Structure (declared in .h) pour que cette fonction accepte (au moins) 2 parametres au lieu d'un
	my_game = param;

	int		move;
	move = 0;

	int		collectibles_amount;											// A chaque touche pressée, on check le nombre de collectibles restant
	collectibles_amount = get_collectibles_left(*my_game, true);			// bool parameter probably not useful anymore, run tests & remove it

	if (!my_game || !my_game->player_image || my_game->player_image->count < 1)
		return;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)	// Exit on ESC key
	{
		mlx_close_window(my_game->window);								// don't use mlx_terminate otherwise segfault
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
	print_map_fun(*my_game);			// Only for testing purposes
}

void		bonus_counter(game my_game)		// Not ready yet
{
	char *string_to_display;
	string_to_display = "Step counter";
	mlx_put_string(my_game.window, string_to_display, 10, 1);

	char *number_to_diplay;
	number_to_diplay = ft_itoa(my_game.counter);					// Malloc done here
	mlx_put_string(my_game.window, number_to_diplay, 20, 30);
}
