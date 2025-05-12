#include "so_long.h"

// ‼️‼️‼️ MLX42 NB : 2 forbidden functions mlx_put_pixel  and mlx_resize_image

// ---------------------------------------------------------------------------------------------------------- Click on cross to quit in a clean way. MEM LEAKS ‼️
void ft_clic_exit(void *param) // model = mlx_closefunc
{
	all_mallocs	*free_this;
	free_this = param;

	ft_printf("Brutal exit\n");

	//ft_free_exit(free_this);			// Segfault if kept
}

// --------------------------------------------------------------------- Centraliser le process de chargement de textures + Error handling + Avoid Segfaults ✅
mlx_texture_t	*ft_check_texture(all_mallocs *stuff_to_free, const char *path)
{
	mlx_texture_t	*texture;
	texture = mlx_load_png(path);
	if(!texture)
	{
		ft_printf("Error with this path [%s] : %s\n", path, mlx_strerror(mlx_errno));
		ft_free_exit(stuff_to_free);
		return (NULL);
	}
	return(texture);
}

void ft_key_move(mlx_key_data_t keydata, void *param)
{
	all_mallocs	*pick_variable;	// Structure (declared in .h) pour que cette fonction accepte (au moins) 2 parametres au lieu d'un
	pick_variable = param;

	if (!pick_variable || !pick_variable->player_image || pick_variable->player_image->count < 1)
		return;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(pick_variable->window); // don't use mlx_terminate otherwise segfault
	}

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)		// Quelle touche + Est-elle pressée ?
		pick_variable->player_image->instances[0].x += TILE_SIZE;			// 32 px à droite (1 case)
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		pick_variable->player_image->instances[0].x -= TILE_SIZE;			// [0] (l'instance est stockée dans un tableau) = 1ere fois où l’image a été affichée (donc l’instance à l’écran)
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		pick_variable->player_image->instances[0].y -= TILE_SIZE;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		pick_variable->player_image->instances[0].y += TILE_SIZE;
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

		if(free_this->exit_texture)
			mlx_delete_texture(free_this->exit_texture);

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
