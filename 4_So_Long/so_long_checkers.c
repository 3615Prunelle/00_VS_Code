#include "so_long.h"

int		check_everything(game my_game)
{
// ------------------------------------------------------------------------------------------------------------ Check if walls all around ✅
	if (check_walls(my_game) == 0)
	{
		ft_printf("Error\n>> Sorry, your funky map isn't valid, please make sure they're walls all around !\n\n");
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
	}
// ---------------------------------------------------------------------------------------------------------------------- Check if Player ✅
	tile	player_position;
	player_position = is_player(my_game);
	if ((player_position.line == -1) && (player_position.column == -1))
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
// ---------------------------------------------------------------------------------------------------------------- Check if Collectibles ✅
	int collectibles_amount;
	collectibles_amount = get_collectibles_left(my_game, false);
	if (collectibles_amount == 0)
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function
// ------------------------------------------------------------------------------------------------------------------------ Check if escape ✅
	my_game.escape_position = is_escape (my_game);
	if ((my_game.escape_position.line == -1) && (my_game.escape_position.column == -1))
		return (0);													// ✅ Valgrind ok, everything dealt with in the so_long function

// ---------------------------------------------------------------------------------------- Check si path valide pour escape + Collectibles ✅
	game	my_game_copy;							// Pour ne pas dupliquer le jeu a chaque recursion dans path_valid (autre option : utiliser une static int ?)

	my_game_copy = duplicate_game(my_game);			// Free done below ✅
	if (is_path_valid(player_position, my_game.escape_position, my_game_copy, &collectibles_amount) == false)
	{
		ft_printf("Error\n>> Looks like some elements can't be reached - Check the walls position !\n");
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
			j++;
		else
			return (0);
	}
	i++;
// ------------------------- Verif des lignes in between ----------------------------------- //
	while (i < (my_game.max_lines - 1))	// lines = amount of lines but index lines is -1. Meaning that there are 5 lines, but line[5] is out of the allocated memory
	{
		if ((my_game.content[i][0] == '1') && (my_game.content[i][my_game.max_columns - 2] == '1')) // length -1 is \n so need to put length-2
			i++;
		else
			return (0);
	}
	return (1);
}
// ------------------------------------------------------------------------------ Chercher si un element existe, et retourner sa position ✅
tile	element_position(game my_game, char element, int *counter)
{
	int y = 0;
	int	x = 0;
	*counter = 0;
	tile	element_position;
	element_position.line = -1;							// Return si element not found
	element_position.column = -1;

	while (y < my_game.max_lines)
	{
		x = 0;
		while (x < my_game.max_columns)
		{
			if (my_game.content[y][x] == element)
			{
				(*counter)++;
				element_position.line = y;
				element_position.column = x;
			}
			x++;
		}
		y++;
	}
	return (element_position);
}

tile	is_player(game my_game)
{
	int	player_counter;
	player_counter = 0;

	tile player_position;
	player_position = element_position(my_game, PLAYER, &player_counter);

	if((player_counter == 0) || (player_counter > 1))
	{
		if (player_counter == 0)
			ft_printf("Error\n>> Please invite Diplo to the game !\n");
		else
			ft_printf("Error\n>> No friends allowed! Sorry-not-sorry 🐒\n");
		player_position.line = -1;
		player_position.column = -1;
	}
	return (player_position);
}
// -----------------------------------------------------------------------------  Chercher si au moins un collectible + Combien il y en a ✅
int		get_collectibles_left(game my_game, bool in_game_loop)
{
	int	collectibles_amount;
	collectibles_amount = 0;
	element_position(my_game, COLLECTIBLE, &collectibles_amount);	// On va chercher le nombre de collectibles et retourner la position du dernier trouvé

	if (in_game_loop == false)					// Otherwise it displays the "no collectibles" error message after all collectibles are picked
	{
		if(collectibles_amount == 0)
			ft_printf("Error\n>> Corn-Quest cancelled - Nothing to collect !\n\n");
		if(collectibles_amount == -1)
			ft_printf("Error\n>> Looks like at least one collectible can't be reached - Check the walls position !\n");
	}
	return (collectibles_amount);
}
// -------------------------------------------------------------------------------------------------------- Chercher si une sortie existe ✅
tile	is_escape(game my_game)
{
	int	escape_counter;
	escape_counter = 0;

	tile	escape_position;
	escape_position = element_position(my_game, EXIT, &escape_counter);

	if(escape_counter == 0)
	{
		ft_printf("Error\n>> Corn-Quest cancelled - No way to escape.\n");
		escape_position.line = -1;
		escape_position.column = -1;
	}
	if(escape_counter > 1)
	{
		escape_position.line = -1;
		escape_position.column = -1;
		ft_printf("Error\n>> Corn-Quest cancelled - Too many escapes.\n");
	}
	return (escape_position);
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
bool	is_path_valid(tile player_position, tile destination_position, game my_game_copy, int *total_collectibles)
{
	static int collectibles_amount;
	static int escape_found;
// ---------------------------------------------------------------------------------------------  Verifie que start est dans le rectangle ✅
	if ((player_position.line < 0) || (player_position.column < 0) || (player_position.line > my_game_copy.max_lines) || (player_position.column > my_game_copy.max_columns))
		return (false);
	if (GET_TILE(my_game_copy.content, player_position) == COLLECTIBLE)
		collectibles_amount++;
// -------------------------------------------------------------------------- Est-ce que player est sur la destination (escape/collectible) ✅
	if (player_position.line == destination_position.line && (player_position.column == destination_position.column))
		escape_found = 1;	/* Ne rien return pour l'instant car on doit etre surs que tous les collectibles sont trouvés */
// ---------------------------------------------------------------------------------------------------------- Est-ce qu'on est sur un mur ✅
	if (GET_TILE(my_game_copy.content, player_position) == WALL)
		return (false);
// ------------------------------------------------------------------------------------------- Est-ce qu'on est deja passé sur cette case ✅
	if (GET_TILE(my_game_copy.content, player_position) == VISITAY)
		return (false);
// ----------------------------------------------------------------------------------------- Sauvegarder visite de la case (marquer un V) ✅
	GET_TILE(my_game_copy.content, player_position) = VISITAY;
	if ((collectibles_amount == *total_collectibles) && (escape_found == 1))
		return (true);
	tile	player_up = {player_position.line - 1, player_position.column};
	tile	player_left = {player_position.line, player_position.column - 1};
	tile	player_down = {player_position.line + 1, player_position.column};
	tile	player_right = {player_position.line, player_position.column + 1};
// --------------------------------------------------------------------------------------- Aller en haut puis gauche puis bas puis droite ✅
	if (is_path_valid(player_up, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_left, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_down, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(player_right, destination_position, my_game_copy, total_collectibles))
		return (true);
	return (false);
}
