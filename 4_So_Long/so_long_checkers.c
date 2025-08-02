#include "so_long.h"

bool	check_everything(game *my_game)	// Je passe un pointeur pour libérer la mémoire dans fonctions appelées si erreurs (gain de place norminette)
{
// ------------------------------------------------------------------------------------------------------------ Check if walls all around ✅
	if (!are_walls_approved(*my_game)) // changer param pour my game si tests ok
	{
		ft_printf(ERROR_MESSSAGE_04);
		return (false);
	}
// ---------------------------------------------------------------------------------- Check if all elements are here in the correct amount ✅
	if((!is_element(my_game, PLAYER)) || (!is_element(my_game, ESCAPE)) || (!is_element(my_game, COLLECTIBLE)))
	{
		return (false);		// Message d'erreur géré dans is_element
	}
// --------------------------------------------------------------------------------------- Check si path valide pour Escape + Collectibles ✅
	tile	player_position;
	player_position = get_tile_position(*my_game, PLAYER);

	int collectibles_amount;
	collectibles_amount = get_collectibles_left(*my_game);

	my_game->escape_position = get_tile_position(*my_game, ESCAPE);

	game	my_game_copy;						// Segfault si je ne le fais pas - Pourquoi ? (Initialement créé pour ne pas dupliquer le jeu a chaque recursion dans path_valid (autre option : utiliser une static int ?)
	my_game_copy = duplicate_game(*my_game);	// Free done below ✅
	if (!is_path_valid(player_position, my_game->escape_position, my_game_copy, collectibles_amount))
	{
		free_logic_part(ERROR_MESSSAGE_09, &my_game_copy); // ✅ Free
		return(false);
	}
	free_logic_part(OK_MESSSAGE_01, &my_game_copy);
	return (true);
}

bool	are_walls_approved(game my_game)
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

// ---- ⬇️  Check qu'il y a seulement : 1 joueur + 1 escape / AU MOINS 1 collec ✅
bool	is_element(game *my_game, char element)
{
	int	x;
	int y;
	int element_counter;

	y = 0;
	element_counter = 0;
	while (y < my_game->max_lines)
	{
		x = 0;
		while (x < my_game->max_columns)
		{
			if (my_game->content[y][x] == element)
				(element_counter)++;
			x++;
		}
		y++;
	}
	if (element_counter == 0)
		return(ft_printf(ERROR_MESSSAGE_07), false);
	if ((element_counter > 1) && ((element == 'P') || (element == 'E')))
		return(ft_printf(ERROR_MESSSAGE_08), false);
	return (true);
}


int		get_collectibles_left(game my_game) // Supprimer bool param ?
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
four_moves	moves_options_set_up(tile player_position)
{
	four_moves	all_directions;

	all_directions.player_up.line = player_position.line - 1;
	all_directions.player_up.column = player_position.column;

	all_directions.player_left.line = player_position.line;
	all_directions.player_left.column = player_position.column - 1;

	all_directions.player_down.line = player_position.line + 1;
	all_directions.player_down.column = player_position.column;

	all_directions.player_right.line = player_position.line;
	all_directions.player_right.column = player_position.column + 1;

	return(all_directions);
}
// ---- ⬇️  Verif validité du path ✅
bool	is_path_valid(tile player_position, tile destination_position, game my_game_copy, int total_collectibles)
{
	static int	collectibles_counter;
	static int	escape_found;
	four_moves	all_directions;
// ---------------------------------------------------------------------------------------------  Verifie que start est dans le rectangle ✅
	if ((player_position.line < 0) || (player_position.column < 0) || (player_position.line > my_game_copy.max_lines) || (player_position.column > my_game_copy.max_columns))
		return (false);
	if (TILE_CHAR(my_game_copy.content, player_position) == COLLECTIBLE)
		collectibles_counter++;
// -------------------------------------------------------------------------- Est-ce que player est sur la destination (escape/collectible) ✅
	if (player_position.line == destination_position.line && (player_position.column == destination_position.column))
		escape_found = 1;	/* Ne rien return pour l'instant car on doit etre surs que tous les collectibles sont trouvés */
// ---------------------------------------------------------------------------------------------------------- Est-ce qu'on est sur un mur ✅
	if (TILE_CHAR(my_game_copy.content, player_position) == WALL)
		return (false);
// ------------------------------------------------------------------------------------------- Est-ce qu'on est deja passé sur cette case ✅
	if (TILE_CHAR(my_game_copy.content, player_position) == CHECKED)
		return (false);
// ----------------------------------------------------------------------------------------- Sauvegarder visite de la case (marquer un V) ✅
	TILE_CHAR(my_game_copy.content, player_position) = CHECKED;
	if ((collectibles_counter == total_collectibles) && (escape_found == 1))
		return (true);
	all_directions = moves_options_set_up(player_position);
// --------------------------------------------------------------------------------------- Aller en haut puis gauche puis bas puis droite ✅
	if (is_path_valid(all_directions.player_up, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(all_directions.player_left, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(all_directions.player_down, destination_position, my_game_copy, total_collectibles))
		return (true);
	if (is_path_valid(all_directions.player_right, destination_position, my_game_copy, total_collectibles))
		return (true);
	return (false);
}
