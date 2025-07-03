#include "so_long.h"

bool	check_everything(game my_game)
{
// ------------------------------------------------------------------------------------------------------------ Check if walls all around ✅
	if (!are_walls_approved(my_game))
	{
		ft_printf("Error\n>> Sorry, your funky map isn't valid, please make sure they're walls all around !\n\n");
		return (false);													// ✅ Valgrind ok, everything dealt with in the so_long function
	}
// ---------------------------------------------------------------------------------- Check if all elements are here in the correct amount ✅
	if((!is_element(my_game, PLAYER)) || (!is_element(my_game, ESCAPE)) || (!is_element(my_game, COLLECTIBLE)))
	{
		return (false);													// TBD - Valgrind ok, everything dealt with in the so_long function
	}
// --------------------------------------------------------------------------------------- Check si path valide pour Escape + Collectibles ✅
	tile	player_position;
	player_position = get_tile_position(my_game, PLAYER);

	int collectibles_amount;
	collectibles_amount = get_collectibles_left(my_game, false);

	my_game.escape_position = get_tile_position(my_game, ESCAPE);

	game	my_game_copy;							// Pour ne pas dupliquer le jeu a chaque recursion dans path_valid (autre option : utiliser une static int ?)

	my_game_copy = duplicate_game(my_game);			// Free done below ✅
	if (is_path_valid(player_position, my_game.escape_position, my_game_copy, collectibles_amount) == false)
	{
		ft_printf("Error\n>> Looks like some elements can't be reached - Check the walls position !\n");
		free_game(&my_game_copy);
		return (false);													// ✅ Copy freed here, game freed in so_long function
	}
	free_game(&my_game_copy);

	return (true);										// If successful
}

bool		are_walls_approved(game my_game)
{
	int i = 0;
	int j = 0;
// ------------------------- Verif de la 1ere & derniere ligne ----------------------------- //
	while ((my_game.content[i][j] != '\n') && (my_game.content[my_game.max_lines - 1][j] != '\n'))
	{
		if ((my_game.content[i][j] == '1') && (my_game.content[my_game.max_lines - 1][j] == '1'))
			j++;
		else
			return (false);
	}
	i++;
// ------------------------- Verif des lignes in between ----------------------------------- //
	while (i < (my_game.max_lines - 1))	// lines = amount of lines but index lines is -1. Meaning that there are 5 lines, but line[5] is out of the allocated memory
	{
		if ((my_game.content[i][0] == '1') && (my_game.content[i][my_game.max_columns - 2] == '1')) // length -1 is \n so need to put length-2
			i++;
		else
			return (false);
	}
	return (true);
}
// ------------------------------------------------------------------------------ Chercher si un element existe, et retourner sa position ✅
tile	get_tile_position(game my_game, char element)
{
	int y = 0;
	int	x = 0;
	tile	element_position;
	element_position.line = -1;							// Return si element not found - Utile pour debug
	element_position.column = -1;

	while (y < my_game.max_lines)
	{
		x = 0;
		while (x < my_game.max_columns)
		{
			if (my_game.content[y][x] == element)
			{
				element_position.line = y;
				element_position.column = x;
			}
			x++;
		}
		y++;
	}
	return (element_position);
}

bool	is_element(game my_game, char element)			// Uniquement pour check_everything
{
	// Check qu'il y a seulement : 1 joueur + 1 escape // AU MOINS 1 collec
	int y = 0;
	int	x = 0;
	int counter = 0;

	while (y < my_game.max_lines)
	{
		x = 0;
		while (x < my_game.max_columns)
		{
			if (my_game.content[y][x] == element)
			{
				(counter)++;
			}
			x++;
		}
		y++;
	}
	if (counter == 0)
	{
		ft_printf("Error\n>> Something is missing - Pick & Choose : Player / Collectible / Exit\n");
		return(false);
	}
	if ((counter > 1) && ((element == 'P') || (element == 'E')))
	{
		ft_printf("Error\n>> Too many ... - Pick & Choose : Players / Escapes\n");
		return(false);
	}
	return (true);
}

int		get_collectibles_left(game my_game, bool in_game_loop) // Supprimer bool param ?
{
	int	collectibles_amount;
	collectibles_amount = 0;

	int y = 0;
	int	x = 0;

	while (y < my_game.max_lines)
	{
		x = 0;
		while (x < my_game.max_columns)
		{
			if (my_game.content[y][x] == COLLECTIBLE)
			{
				collectibles_amount++;
			}
			x++;
		}
		y++;
	}

	return (collectibles_amount);
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
bool	is_path_valid(tile player_position, tile destination_position, game my_game_copy, int total_collectibles)
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
	if ((collectibles_amount == total_collectibles) && (escape_found == 1))
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
