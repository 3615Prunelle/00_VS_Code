#include "so_long.h"

tile	target_position(game my_game, int move)
{
	tile	target;
	tile player;

	player = get_tile_position(my_game, PLAYER);
	if (move == RIGHT)						// only the target reference is updated, not the player one (yet)
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
	return(target);
}

// ---- ⬇️ Vérifier chaque possibilité de mouvement + Create counter ✅
void	move_player_logic(game my_game, int move)
{
	static int	step_counter;
	tile player;
	tile	target;

	player = get_tile_position(my_game, PLAYER);
	target = target_position(my_game, move);

	my_game.player_image->instances->z = 44; // Change depth so player is above exit
	my_game.escape_image->instances->z = 36;

// ----------------------------------------------------------------- Faire réapparaitre la sortie s'il reste des collectibles ✅
	if ((player.column == my_game.escape_position.column) && (player.line == my_game.escape_position.line) && (get_collectibles_left(my_game) > 0))
	{
		ESCAPE_POSITION = 'E';	// ✅ Keeping the escape position somewhere or it will be deleted (forever) after pass in is_move_allowed
	}
	if (is_move_allowed(my_game, target))
	{
		TARGET_POSITION = 'P';
		if ((player.column == my_game.escape_position.column) && (player.line == my_game.escape_position.line))
			PLAYER_POSITION = 'E';
		else
			PLAYER_POSITION = '0';

		player.line = target.line;			// Update de la position du player
		player.column = target.column;		// Idem
		step_counter++;
		bonus_counter(my_game, step_counter);
		return;
	}
	return;
}

void	move_player_graphic(game *my_game)
{
	// Sera -1 si player est sur la sortie et qu'il veut bouger dans un mur
	tile updated_player_position = get_tile_position(*my_game, PLAYER);
	if (updated_player_position.column != -1)
	{
		my_game->player_image->instances[0].x = updated_player_position.column * TILE_SIZE;		// Déplacement de l'image en prenant en compte l'échelle du jeu
		my_game->player_image->instances[0].y = updated_player_position.line * TILE_SIZE;		// 1 case (dans représentation non graphique) = 72 pixels (rep visuelle)
	}
	else // update position player = -1 après avoir tenté exit, on a une segfault
	{
		my_game->content[my_game->escape_position.line][my_game->escape_position.column] = PLAYER;
	}
}

bool	is_move_allowed(game my_game, tile target)
{
	if (TARGET_POSITION == '0' || TARGET_POSITION == 'C' || TARGET_POSITION == 'E')
	{
		return(true);
	}
	return (false);
}

void	delete_collectible_instance(game *my_game, int collectibles_amount)
{
	// -------------------------------------------------------------------------- If on collectible : delete collectible instance ✅
	size_t	index;

	index = 0;
	while (index < my_game->collectible_image->count)
	{
		if (my_game->player_image->instances[0].x == my_game->collectible_image->instances[index].x
			&& my_game->player_image->instances[0].y == my_game->collectible_image->instances[index].y)
		{
			my_game->collectible_image->instances[index].enabled = false;
		}
		index++;
	}
	// --------------------------------------------------------------------------- If on escape + collectibles fetched : exit game ✅
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
}
// Will be deleted before submit
void	print_map_fun(game my_game)
{
	for(int p = 0; p < my_game.max_lines; p++)
	{
		for (int i = 0; i < my_game.max_columns; i++)
		{
			switch (my_game.content[p][i])
			{
			case 'P':
				ft_printf(EMOJI_PLAYER);
				break;
			case 'C':
				ft_printf(EMOJI_COLLECTIBLE);
				break;
			case 'E':
				ft_printf(EMOJI_ESCAPE);
				break;
			case '1':
				ft_printf(EMOJI_WALL);
				break;
			case '0':
				ft_printf(EMOJI_GROUND);
				break;
			case '\n':
				ft_printf("\n");
				break;
			default:
				break;
			}
		}
	}
}
