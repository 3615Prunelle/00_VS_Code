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

// -------------------------------------------------------------------  Vérifier chaque possibilité de mouvement + Create counter ✅
void	player_move(game my_game, int move)
{
	tile player;
	player = get_tile_position(my_game, PLAYER);

	tile	target;
	target = target_position(my_game, move);

	static int	step_counter;
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

bool	is_move_allowed(game my_game, tile target)
{
	if (TARGET_POSITION == '0' || TARGET_POSITION == 'C' || TARGET_POSITION == 'E')
	{
		return(true);
	}
	return (false);
}

// Will be deleted before submit
void	print_map(game my_game)
{
	for(int p = 0; p < my_game.max_lines; p++)
		ft_printf("%s", my_game.content[p]);
}

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
