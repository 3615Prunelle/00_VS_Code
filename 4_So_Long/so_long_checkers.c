#include "so_long.h"

int			check_everything(game my_game)
{
// ------------------------------------------------------------------------------------------------------------ Check if walls all around ✅
	if (check_walls(my_game) == 0)
	{
		printf("Error\n>> Sorry, your funky map isn't valid, please make sure they're walls all around !\n\n");
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
	}
// ---------------------------------------------------------------------------------------------------------------------- Check if Player ✅
	tile	player;
	player = is_player(my_game);
	player.type = 'P';
	if ((player.line == -1) && (player.column == -1))
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
// ---------------------------------------------------------------------------------------------------------------- Check if Collectibles ✅
	int collec_left;
	collec_left = is_collec(my_game, player, false);
	if (collec_left == 0)
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
// ------------------------------------------------------------------------------------------------------------------------ Check if Exit ✅
	tile	exit;
	exit = is_exit (my_game);
	if ((exit.line == -1) && (exit.column == -1))
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function

// ---------------------------------------------------------------------------------------- Check si path valide pour Exit + Collectibles ✅
	game	my_game_copy;							// Pour ne pas dupliquer le jeu a chaque recursion dans path_valid (autre option : utiliser une static int ?)
	my_game_copy = duplicate_game(my_game);			// Free done below ✅
	if (is_path_valid(player, &exit, my_game_copy, &collec_left) == false)
	{
		printf("Error\n>> Looks like some elements can't be reached - Check the walls position !\n");
		free_game(&my_game_copy);
		return (0);													// ✅ Copy freed here, game freed in so_long function
	}
	free_game(&my_game_copy);

	return (1);										// If successful
}

int		check_walls(game my_game)
{
	int i = 0;
	int j = 0;
// ------------------------- Verif de la 1ere & derniere ligne ----------------------------- //
	while ((my_game.content[i][j] != '\n') && (my_game.content[my_game.max_lines - 1][j] != '\n'))
	{
		if ((my_game.content[i][j] == '1') && (my_game.content[my_game.max_lines - 1][j] == '1'))
		{
			j++;
		}
		else
		{
			return (0);
		}
	}
	i++;
// ------------------------- Verif des lignes in between ----------------------------------- //
	while (i < (my_game.max_lines - 1))	// lines = amount of lines but index lines is -1. Meaning that there are 5 lines, but line[5] is out of the allocated memory
	{
		if ((my_game.content[i][0] == '1') && (my_game.content[i][my_game.max_columns - 2] == '1')) // length -1 is \n so need to put length-2
		{
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
// ------------------------------------------------------------------------------ Chercher si un element existe, et retourner sa position ✅
tile	is_element(game my_game, char element, int *counter)
{
	int y = 0;
	int	x = 0;
	*counter = 0;
	tile	pos_element;
	pos_element.line = -1;							// Retournera ca si pas element not found
	pos_element.column = -1;

	while (y < my_game.max_lines)
	{
		x = 0;
		while (x < my_game.max_columns)
		{
			if (my_game.content[y][x] == element)
			{
				(*counter)++;
				pos_element.line = y;
				pos_element.column = x;
			}
			x++;
		}
		y++;
	}
	return (pos_element);
}

tile	is_player(game my_game)
{
	int	player_counter;
	player_counter = 0;

	tile player;
	player = is_element(my_game, PLAYER, &player_counter);

	if((player_counter == 0) || (player_counter > 1))
	{
		if (player_counter == 0)
			printf("Error\n>> How do you expect to play a game if there's no player?\n");
		else
			printf("Error\n>> Only one dino allowed! Sorry-not-sorry 🐒\n");
		player.line = -1;
		player.column = -1;
	}
	return (player);
}
// -----------------------------------------------------------------------------  Chercher si au moins un collectible + Combien il y en a ✅
int		is_collec(game my_game, tile player, bool in_game_loop)
{
	int	collectibles_counter;
	collectibles_counter = 0;
	is_element(my_game, COLLECTIBLE, &collectibles_counter);	// On va chercher le nombre de collectibles

	if (in_game_loop == false)					// Otherwise it displays the "no collectibles" error message after all collectibles are picked
	{
		if(collectibles_counter == 0)
			printf("Error\n>> Corn-Quest cancelled - Nothing to collect ! 🌽\n\n");
		if(collectibles_counter == -1)
			printf("Error\n>> Looks like at least one collectible can't be reached - Check the walls position !\n");
	}
	return (collectibles_counter);
}
// -------------------------------------------------------------------------------------------------------- Chercher si une sortie existe ✅
tile	is_exit(game my_game)
{
	int	exit_counter;
	exit_counter = 0;

	tile	exit;
	exit = is_element (my_game, EXIT, &exit_counter);

	if(exit_counter == 0)
	{
		printf("Error\n>> Corn-Quest cancelled - No way to escape.\n");
		exit.line = -1;
		exit.column = -1;
	}
	if(exit_counter > 1)
	{
		exit.line = -1;
		exit.column = -1;
		printf("Error\n>> Corn-Quest cancelled - Too many escapes.\n");
	}
	return (exit);
}

game	duplicate_game(game my_game)
{
// ----------------------------------------------- Copie de la map pour eviter de mettre de changer quoi ce que soit sur la map d'origine ✅
	game	my_game_copy;
	my_game_copy.max_columns = my_game.max_columns;
	my_game_copy.max_lines = my_game.max_lines;

	my_game_copy.content = ft_calloc(my_game.max_lines, sizeof(char *));				// FREE dans fonction appelante ✅
	if (!my_game_copy.content)
		my_game_copy.content = NULL;													// Fait ca car je ne peux pas return NULL
	int y = 0;
	while (y < my_game.max_lines)
	{
// ---------------------------------------------------------- Calloc toutes les lignes car on utilise pas GNL cette fois (sinon segfault) ✅
		my_game_copy.content[y] = ft_calloc(my_game.max_columns, sizeof(char));			// FREE dans fonction appelante ✅
		if (!my_game_copy.content[y])
			my_game_copy.content = NULL;												// Fait ca car je ne peux pas return NULL
		my_game_copy.content[y] = ft_memcpy(my_game_copy.content[y], my_game.content[y], (size_t)my_game.max_columns);
		y++;
	}
	return (my_game_copy);
}
// --------------------------------------------------------------------------------------------------------------- Verif validité du path ✅
bool	is_path_valid(tile player, tile *destination, game my_game_copy, int *total_collectibles)
{
	static int collectibles_counter;
	static int exit_found;
// ---------------------------------------------------------------------------------------------  Verifie que start est dans le rectangle ✅
	if ((player.line < 0) || (player.column < 0) || (player.line > my_game_copy.max_lines) || (player.column > my_game_copy.max_columns))
		return (false);
	if (GET_TILE(my_game_copy.content, player) == COLLECTIBLE)
		collectibles_counter++;
// -------------------------------------------------------------------------- Est-ce que player est sur la destination (exit/collectible) ✅
	if (player.line == destination->line && (player.column == destination->column))
		exit_found = 1;	/* Ne rien return pour l'instant car on doit etre surs que tous les collectibles sont trouvés */
// ---------------------------------------------------------------------------------------------------------- Est-ce qu'on est sur un mur ✅
	if (GET_TILE(my_game_copy.content, player) == WALL)
		return (false);
// ------------------------------------------------------------------------------------------- Est-ce qu'on est deja passé sur cette case ✅
	if (GET_TILE(my_game_copy.content, player) == VISITAY)
		return (false);
// ----------------------------------------------------------------------------------------- Sauvegarder visite de la case (marquer un V) ✅
	GET_TILE(my_game_copy.content, player) = VISITAY;
	if ((collectibles_counter == *total_collectibles) && (exit_found == 1))
		return (true);
	tile	player_up = {player.line - 1, player.column};
	tile	player_left = {player.line, player.column - 1};
	tile	player_down = {player.line + 1, player.column};
	tile	player_right = {player.line, player.column + 1};
// --------------------------------------------------------------------------------------- Aller en haut puis gauche puis bas puis droite ✅
	if (is_path_valid(player_up, destination, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_left, destination, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_down, destination, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_right, destination, my_game_copy, total_collectibles))
		return (true);
	return (false);
}
