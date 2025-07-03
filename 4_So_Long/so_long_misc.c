#include "so_long.h"
// -------------------------------------------------------------------  Vérifier chaque possibilité de mouvement + Create counter ✅

tile	target_position(game *my_game, int move)
{
	tile	target;
	tile player;
	player = is_player(*my_game);

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

bool	player_move(game *my_game, int move)
{
	tile player;
	player = is_player(*my_game);

	tile	target;
	target = target_position(my_game, move);

	my_game->counter++;

// ----------------------------------------------------------------- Faire réapparaitre la sortie s'il reste des collectibles ‼️
	if ((player.column == my_game->escape_position.column) && (player.line == my_game->escape_position.line) && (is_collec(*my_game, true) > 0))
	{
		ESCAPE_POSITION = 'E';	// ✅ Keeping the escape position somewhere or it will be deleted (forever) after pass in check_target
		// my_game->content[my_game->escape_position.line][my_game->escape_position.column] = 'E';
	}
	if (check_target(my_game, player, target))	// That's where the player position changes and gets updated
	{
		TARGET_POSITION = 'P';
		if ((player.column == my_game->escape_position.column) && (player.line == my_game->escape_position.line))
			PLAYER_POSITION = 'E';
		else
			PLAYER_POSITION = '0';

		player.line = target.line;			// Update de la position du player
		player.column = target.column;		// Idem
		return(true);
	}
	return(false);
}

bool	check_target(game *my_game, tile player, tile target) // Remove player param
{
	if (TARGET_POSITION == '0' || TARGET_POSITION == 'C' || TARGET_POSITION == 'E')	// ✅ Keep the escape position somewhere or it will be deleted (forever) after this pass
	{
		// If target collectible
		// Move allowed
		// Fetch collectible position
		return(true);
	}
	return (false);
}
// -------------------------------------------------------------------------------------------- Edit & use when things get spicy ✅
void	free_game(game *any)
{
	while (any->max_lines > 0)
	{
		free(any->content[any->max_lines-1]);
		any->max_lines--;
	}
	free(any->content);
}
void	free_gnl_stuff(char **line, int *fd)
{
	free(*line);			// char **line etant l'adresse d'un pointeur, char *line est donc un pointeur, qu'on free [...]
	*line = NULL;			// [...] puis remet a zero
	close(*fd);				// Dereference le pointeur vers fd pour le fermer - Fermer un fd est important pour eviter les fd leaks
	get_next_line(-1);		// Force GNL to free its static buffer
}
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
				ft_printf(PLA);
				break;
			case 'C':
				ft_printf(COL);
				break;
			case 'E':
				ft_printf(EXI);
				break;
			case '1':
				ft_printf(WAL);
				break;
			case '0':
				ft_printf(EMP);
				break;
			case '\n':
				ft_printf("\n");
				break;
			case VISITAY:					// Remove when I get out this goddam rabbit hole
				ft_printf("🟥");
				break;
			default:
				break;
			}
		}
	}
}
