#include "so_long.h"
// -------------------------------------------------------------------  Définir chaque possibilité de mouvement + Create counter ✅
tile	player_move(game my_game, tile player, tile exit)
{
	tile	target;
	int	move;
	static int	counter;
	scanf ("%d", &move);

	while ((move != RIGHT) && (move != LEFT) && (move != UP) && (move != DOWN))
	{
		printf ("Command not recognized - Only 4(left) 8(up) 6(right) 2(down) are accepted - Try again.\n");
		scanf ("%d", &move);
	}
	counter++;
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
// -------------------------------------------------------------------- Faire réapparaitre la sortie s'il reste des collectibles ✅
	if ((player.column == exit.column) && (player.line == exit.line) && (is_collec(my_game, player, true) != 0))
	{
		player = check_target(my_game, player, target);
		EXIT_POSITION = 'E';								// ✅ Keeping the exit position somewhere or it will be deleted (forever) after pass in check_target
	}
	else
		player = check_target(my_game, player, target);		// That's where the player position changes and gets updated
	printf ("Diplo made %i steps to far\n", counter);
	return (player);
}
tile	check_target(game my_game, tile player, tile target)
{
	if (TARGET_POSITION == '0' || TARGET_POSITION == 'C' || TARGET_POSITION == 'E')	// ✅ Keep the exit position somewhere or it will be deleted (forever) after this pass
	{
		TARGET_POSITION = 'P';
		PLAYER_POSITION = '0';				// si if dans player_move pose probleme, faire un if ici (si play_pos = exi_pos + collectibles left, mettre un E a la place du 0)
		player.line = target.line;			// Update de la position du player
		player.column = target.column;		// Idem
	}
	return (player);
}
// -------------------------------------------------------------------------------------------- Edit & use when things get spicy ✅
void		free_game(game *any)
{
	while (any->max_lines > 0)
	{
		free(any->content[any->max_lines-1]);
		any->max_lines--;
	}
	free(any->content);
}
void		free_gnl_stuff(char **line, int *fd)
{
	free(*line);			// char **line etant l'adresse d'un pointeur, char *line est donc un pointeur, qu'on free [...]
	*line = NULL;			// [...] puis remet a zero
	close(*fd);				// Dereference le pointeur vers fd pour le fermer - Fermer un fd est important pour eviter les fd leaks
	get_next_line(-1);		// Force GNL to free its static buffer
}

void		print_map(game my_game)
{
	for(int p = 0; p < my_game.max_lines; p++)
		printf("%s", my_game.content[p]);
}
void		print_map_fun(game my_game)
{
	for(int p = 0; p < my_game.max_lines; p++)
	{
		for (int i = 0; i < my_game.max_columns; i++)
		{
			switch (my_game.content[p][i])
			{
			case 'P':
				printf(PLA);
				break;
			case 'C':
				printf(COL);
				break;
			case 'E':
				printf(EXI);
				break;
			case '1':
				printf(WAL);
				break;
			case '0':
				printf(EMP);
				break;
			case '\n':
				printf("\n");
				break;
			case VISITAY:					// Remove when I get out this goddam rabbit hole
				printf("🟥");
				break;
			default:
				break;
			}
		}
	}
}
