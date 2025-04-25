#include "so_long.h"
// ----------------------------- Définir chaque possibilité de mouvement ----------------------------- //
position	player_move(char **map, position player, position exit, int lines)
{
	position	target;
	int	move;
	scanf ("%d", &move);			// For later, input from keyboard
	//move = RIGHT;

	if (move == RIGHT)				// In this function, only the target reference is changed, not the player one
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
// ------------------------- ✅ Trouver un moyen de faire réapparaitre la sortie s'il reste des collectibles ----------------------------- //
	if ((player.column == exit.column) && (player.line == exit.line) && (is_collec(map, lines, true) != 0))
	{
		player = check_target(map, player, target);
		EXIT_POSITION = 'E';
	}
// ------------------------- / Success ----------------------------- //
	else
		player = check_target(map, player, target);			// that's where the player position changes and gets updated
	return (player);
}
position	check_target(char **map, position player, position target)
{
	if (TARGET_POSITION == '0' || TARGET_POSITION == 'C' || TARGET_POSITION == 'E')	// ‼️Keep the exit position somewhere or it will be deleted (forever) after this pass
	{
		TARGET_POSITION = 'P';
		PLAYER_POSITION = '0';					// si if dans player_move pose probleme, faire un if ici (si play_pos = exi_pos + collectibles left, mettre un E a la place du 0)
		player.line = target.line;				// Update de la position du player
		player.column = target.column;			// Update de la position du player
	}
	return (player);
}
// ------------------------- ✅ Chercher si un player existe, et retourner sa position ----------------------------- //
position	is_player(char **map, int lines)
{
	int y = 0;
	int	x = 0;
	int p_index;
	int	player_counter = 0;
	position	player;
	/* option 2 : if I want to return (NULL) in case or error, I need to declare a pointer to player (and return it), but that implies a malloc/free.
	(I'd need to allocate memory, so that the memory still exists after the function ends.
	Otherwise, I’d be returning a pointer to something that disappears when the function returns (aka “dangling pointer”).) */

	while (y < lines)
	{
		x = 0;
		if(ft_strchr(map[y], 'P'))
		{
			while (map[y][x] != '\0')
			{
				if (map[y][x] == 'P')
				{
					player_counter++;
				}
				x++;

			}
			p_index = (ft_strchr(map[y], 'P')) - map[y]; // because adresse de 'P' = 0x40 53 62 | Adresse 0x40 53 60 = p_index 0 de la ligne y
			player.line = y;
			player.column = p_index;
		}
		y++;
	}
	if((player_counter == 0) || (player_counter > 1))
	{
		if (player_counter == 0)
		printf("How do you even expect to play a game if there's no player? ⛔\n");
		else
		printf("Only one dino allowed! Sorry-not-sorry 🐒\n");
		player.line = -1;
		player.column = -1;
	}
	return (player);
}
// ------------------------- ‼️ Conditions de non validité de la carte ----------------------------- //

int			check_walls(char **map, int lines, int length)
{
	/* Walls all around
Idee : Fonction qui verifie que a line[0] et ligne [strlen] il y a 1 + full 1ere et last line */
	int i = 0;
	// check si ligne 0 & last = only 1
	// check toutes les lignes in between 1 at start + end
	while (map[0])

if ((map[0] != '1') && (map[length] != '1'))
	{
		printf("Sorry, your funky map isn't valid, please make sure they're walls all around !\n");
		return (0);
	}
	return (1);
}

void		is_map_valid(char **map)
{
	/*	• The map must be rectangular. ✅
		• The map must be enclosed/surrounded by walls. If it is not, the program must return an error.
		• You must verify if there is a valid path in the map.
		• You must be able to parse any kind of map, as long as it respects the above rules.
		• If any misconfiguration is encountered in the file, the program must exit cleanly, and return "Error\n" followed by an explicit error message of your choice. */



/* Valid path
Idee : No clue */

}
// ------------------------- ‼️ Create a counter ----------------------------- //

// ------------------------- ✅ Chercher si une sortie existe ----------------------------- //
int			is_exit(char **map, int lines, position *exit)
{
	int j = 0;
	int	index = 0;
	int	exit_counter = 0;

	while (j < lines)
	{
		index = 0;
		if(ft_strchr(map[j], 'E'))
		{
			while (map[j][index] != '\0')
			{
				if (map[j][index] == 'E')
				{
					exit->line = j;
					exit->column = index;
					exit_counter++;
				}
				index++;
			}
		}
		j++;
	}
	if(exit_counter == 0)
		printf("Dino-Quest cancelled - No way to escape.\n");
	if(exit_counter > 1)
	{
		exit_counter = 0;
		printf("You stole too many scooters and you've been caught - Game over.\n");
	}
	return (exit_counter);
}
// ------------------------- ✅ Chercher si au moins un collectible, et combien il y en a ----------------------------- //
int			is_collec(char **map, int lines, bool in_loop)
{
	int j = 0;
	int	index = 0;
	int	collectibles_counter = 0;

	while (j < lines)
	{
		index = 0;
		if(ft_strchr(map[j], 'C'))
		{
			while (map[j][index] != '\0')
			{
				if (map[j][index] == 'C')
				{
					collectibles_counter++;
				}
				index++;
			}
		}
		j++;
	}
	if (in_loop == false)					// otherwise it displays the "no collectibles" error message in the while loop
	{
		if(collectibles_counter == 0)
			printf("Dino-Quest cancelled - Nothing to collect ! 🌽\n");
		if(collectibles_counter > (lines*2))
			printf("Gosh, that's a lot of corn ! 🌽\n");
	}
	return (collectibles_counter);
}
// ------------------------- ‼️ Use when things get spicy ----------------------------- //
void		freeee(void **address_of_anything)
{
	if (*address_of_anything)	// deferencing once = accessing the pointer itself
	{
		free(*address_of_anything);
		*address_of_anything = NULL;
	}
}
void		print_map(char **map, int lines)
{
	printf("\nUpdated map :\n\n");
	for(int p = 0; p < lines; p++)
		printf("%s", map[p]);
}
void		print_map_fun(char **map, int lines, int col)
{
	printf("\nFun map :\n\n");
	for(int p = 0; p < lines; p++)
	{
		for (int i = 0; i < col; i++)
		{
			switch (map[p][i])
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
			default:
				break;
			}
		}
	}
}
