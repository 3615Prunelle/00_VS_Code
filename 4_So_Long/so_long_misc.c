#include "so_long.h"

// Only the target reference is updated, not the player one (yet)
tile	target_position(s_game game, int move)
{
	tile	target;
	tile	player;

	player = get_tile_position(game, PLAYER);
	if (move == RIGHT)
	{
		target.line = player.line;
		target.column = player.column + 1;
	}
	else if (move == LEFT)
	{
		target.line = player.line;
		target.column = player.column - 1;
	}
	else if (move == UP)
	{
		target.line = player.line - 1;
		target.column = player.column;
	}
	else if (move == DOWN)
	{
		target.line = player.line + 1;
		target.column = player.column;
	}
	return (target);
}

// Vérifier chaque possibilité de mouvement
// Create counter
// Update de la position du player
// If need shell testing, use print_map_fun(game); here
void	move_player_logic(s_game game, int move)
{
	static int	step_counter;
	tile		player;
	tile		target;

	player = get_tile_position(game, PLAYER);
	target = target_position(game, move);
	if (is_move_allowed(game, target))
	{
		TARGET = 'P';
		if ((player.column == game.escape_pos.column)
			&& (player.line == game.escape_pos.line))
			PLAYER_POSITION = 'E';
		else
			PLAYER_POSITION = '0';
		player.line = target.line;
		player.column = target.column;
		step_counter++;
		bonus_counter(game, step_counter);
		return ;
	}
	return ;
}

// Updated_player_pos sera -1 si P est sur la sortie et qu'il veut bouger dans un mur
// Si pas -1 : Déplacement de l'image en prenant en compte l'échelle du jeu
// 1 case (dans représentation non graphique) = 72 pixels (rep visuelle)
// Else{} is to update position player (sinon -1 = segfault)
void	move_player_graphic(s_game *game)
{
	tile	updated_player_pos;

	updated_player_pos = get_tile_position(*game, PLAYER);
	if (updated_player_pos.column != -1)
	{
		P_IMG_INSTANCE[0].x = updated_player_pos.column * TILE_SIZE;
		P_IMG_INSTANCE[0].y = updated_player_pos.line * TILE_SIZE;
	}
	else
	{
		game->content[game->escape_pos.line][game->escape_pos.column] = PLAYER;
	}
}

bool	is_move_allowed(s_game game, tile target)
{
	if (TARGET == '0' || TARGET == 'C' || TARGET == 'E')
	{
		return (true);
	}
	return (false);
}

// While loop : If on collectible : delete collectible instance
// If : if on escape + collectibles fetched : exit game
void	delete_collectible_instance(s_game *game)
{
	size_t	index;
	int		ctibles_amount;

	index = 0;
	ctibles_amount = get_collectibles_left(*game);
	while (index < COLLECTIBLE_IMG->count)
	{
		if (P_IMG_INSTANCE[0].x == C_IMG_INSTANCE[index].x
			&& P_IMG_INSTANCE[0].y == C_IMG_INSTANCE[index].y)
		{
			C_IMG_INSTANCE[index].enabled = false;
		}
		index++;
	}
	if (ctibles_amount == 0)
	{
		if (P_IMG_INSTANCE[0].x == E_IMG_INSTANCE[0].x
			&& P_IMG_INSTANCE[0].y == E_IMG_INSTANCE[0].y)
		{
			E_IMG_INSTANCE[0].enabled = false;
			mlx_close_window(WINDOW);
		}
		index++;
	}
}

// Will be deleted before submit
// void	print_map_fun(s_game game)
// {
// 	for (int p = 0; p < game.max_lines; p++)
// 	{
// 		for (int i = 0; i < game.max_columns; i++)
// 		{
// 			switch (game.content[p][i])
// 			{
// 			case 'P':
// 				ft_printf(EMOJI_PLAYER);
// 				break ;
// 			case 'C':
// 				ft_printf(EMOJI_COLLECTIBLE);
// 				break ;
// 			case 'E':
// 				ft_printf(EMOJI_ESCAPE);
// 				break ;
// 			case '1':
// 				ft_printf(EMOJI_WALL);
// 				break ;
// 			case '0':
// 				ft_printf(EMOJI_GROUND);
// 				break ;
// 			case '\n':
// 				ft_printf("\n");
// 				break ;
// 			default:
// 				break ;
// 			}
// 		}
// 	}
// }
