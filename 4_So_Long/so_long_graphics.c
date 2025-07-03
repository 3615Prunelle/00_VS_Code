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
		ft_printf("Failed to load PNG into texture - Path to PNG : [%s] - Error : [%s]\n", path, mlx_strerror(mlx_errno));
		//mlx_terminate(game_window);	// Destroy and clean up all images and mlx resources.
		// ‼️ Free everything before every exit (or create function that does it)
		exit (1);
	}
	//stuff_to_free->texture =	texture;

// -------------------------------------------------------------------------- Convert the texture to a diplayable image ✅Ⓜ️🆓
	mlx_image_t *image;															// Set up image buffer - Note : mlx_image_t doit etre toujours un ptr
	if (!(image = mlx_texture_to_image(game_window, texture)))			// Create a displayable image from texture data - MLX MALLOC DONE HERE ‼️
	{
		ft_printf("Error in allocating new image buffer\n");
		//mlx_terminate(game_window);	// Destroy and clean up all images and mlx resources.
		exit (1);
	}
	//stuff_to_free->image =	image;
	return(image);
}
