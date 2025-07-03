#include "so_long.h"

// ------------------------------------------------------------------------------------------------ Quit in a clean way when clic on cross. MEM LEAKS ‼️
void	free_before_exit(void *param) // model = mlx_closefunc
{
	all_mallocs	*free_this;
	free_this = param;

	ft_printf("Brutal exit\n");

	//ft_free_exit(free_this);			// Segfault if kept
}

void	key_actions(mlx_key_data_t keydata, void *param)
{
	game	*my_game;	// Structure (declared in .h) pour que cette fonction accepte (au moins) 2 parametres au lieu d'un
	my_game = param;

	int		move;
	move = 0;

	int		collectibles_left;											// A chaque touche pressée, on check le nombre de collectibles restant
	collectibles_left = is_collec(*my_game, true);						// bool parameter probably not useful anymore, run tests & remove it
	// Cette fonction appelle element_position, qui renvoie la position du dernier collectible

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

	player_move(my_game, move);			// Cette fonction ne s'occupe que du déplacement du joueur dans le fonctionnement interne du jeu

	char *number_to_diplay;
	number_to_diplay = ft_itoa(my_game->counter);	// Malloc done here
	mlx_put_string(my_game->window, number_to_diplay, 20, 30);

	tile updated_player_position = is_player(*my_game);
	my_game->player_image->instances[0].x = updated_player_position.column * TILE_SIZE;		// Déplacement de l'image en prenant en compte l'échelle du jeu
	my_game->player_image->instances[0].y = updated_player_position.line * TILE_SIZE;		// 1 case (dans représentation non graphique) = 72 pixels (rep visuelle)

	int	index = 0;
	while (index < my_game->collectible_image->count)
	{
		if (my_game->player_image->instances[0].x == my_game->collectible_image->instances[index].x
			&& my_game->player_image->instances[0].y == my_game->collectible_image->instances[index].y)
		{
			my_game->collectible_image->instances[index].enabled = false;
		}
		index++;
	}
	if (collectibles_left == 0)
	{
		if (my_game->player_image->instances[0].x == my_game->escape_image->instances[0].x
			&& my_game->player_image->instances[0].y == my_game->escape_image->instances[0].y)
		{
			my_game->escape_image->instances[0].enabled = false;
			mlx_close_window(my_game->window);
		}
		index++;
	}
	print_map_fun(*my_game);
}

// ------------------------------------------------------------------------------------------- Creer fonction pour libérer les textures when exit game ‼️🆓
void	ft_free_exit(all_mallocs *free_this)
	{
		ft_printf("Tiiime tooo ... Saaay goodbyeeee\n");

		if (!free_this)
			return;
// ‼️ If anything else is allocated : Add it here
// ‼️ If anything was allocated by me (rather than MLX) : Use free (rather than a MLX delete function)
		if(free_this->player_texture)
		{
			mlx_delete_texture(free_this->player_texture);
			free_this->player_texture = NULL;					// Not sure it's necessary
		}

		if(free_this->collec_texture)
			mlx_delete_texture(free_this->collec_texture);

		if(free_this->escape_texture)
			mlx_delete_texture(free_this->escape_texture);

		if(free_this->ground_texture)
			mlx_delete_texture(free_this->ground_texture);

		if(free_this->wall_texture)
			mlx_delete_texture(free_this->wall_texture);

		if(free_this->player_image)
			mlx_delete_image(free_this->window, free_this->player_image);

	// add free(my_game) when previous code is connected to the MLX42 part ‼️

		if(free_this->window)
			mlx_terminate(free_this->window);							// Free game_window

		free(free_this);
		free_this = NULL;
	}
