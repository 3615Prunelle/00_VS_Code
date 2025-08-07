#include "so_long.h"

// Je passe un pointeur en param pour libérer la mémoire dans fonctions appelées si erreurs (gain de place norminette)
// 1st if : Check if walls all around ✅
// 2nd if : Check if all elements are here in the correct amount ✅
// game_copy créé pour ne pas dupliquer le jeu a chaque recursion dans path_valid
bool	check_everything(s_game *game)
{
	tile	player_pos;
	int		ctibles_amount;
	s_game	game_copy;

	if (!are_walls_approved(*game))
	{
		ft_printf(ERROR_MESSSAGE_04);
		return (false);
	}
	if ((!is_element(game, PLAYER)) || (!is_element(game, ESCAPE))
		|| (!is_element(game, COLLECTIBLE)))
	{
		return (false);
	}
	player_pos = get_tile_position(*game, PLAYER);
	ctibles_amount = get_collectibles_left(*game);
	game->escape_pos = get_tile_position(*game, ESCAPE);
	game_copy = duplicate_game(*game);
	if (!is_path_valid(player_pos, game->escape_pos, game_copy, ctibles_amount))
	{
		free_logic_part(ERROR_MESSSAGE_09, &game_copy);
		return (false);
	}
	free_logic_part(OK_MESSSAGE_01, &game_copy);
	return (true);
}

// Step 1 : Verif de la 1ere & derniere ligne
// Step 2 : Verif des lignes in between
bool	are_walls_approved(s_game game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((game.content[i][j] != '\n') && (game.content[game.max_lines
			- 1][j] != '\n'))
	{
		if ((game.content[i][j] == '1') && (game.content[game.max_lines
				- 1][j] == '1'))
			j++;
		else
			return (false);
	}
	i++;
	while (i < (game.max_lines - 1))
	{
		if ((game.content[i][0] == '1') && (game.content[i][game.max_columns
				- 2] == '1'))
			i++;
		else
			return (false);
	}
	return (true);
}

// Return -1 si element not found - Utile pour debug
tile	get_tile_position(s_game game, char element)
{
	int		y;
	int		x;
	tile	element_position;

	y = 0;
	x = 0;
	element_position.line = -1;
	element_position.column = -1;
	while (y < game.max_lines)
	{
		x = 0;
		while (x < game.max_columns)
		{
			if (game.content[y][x] == element)
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

// Check qu'il y a seulement : 1 joueur + 1 escape / AU MOINS 1 collec ✅
bool	is_element(s_game *game, char element)
{
	int	x;
	int	y;
	int	element_counter;

	y = 0;
	element_counter = 0;
	while (y < game->max_lines)
	{
		x = 0;
		while (x < game->max_columns)
		{
			if (game->content[y][x] == element)
				(element_counter)++;
			x++;
		}
		y++;
	}
	if (element_counter == 0)
		return (ft_printf(ERROR_MESSSAGE_07), false);
	if ((element_counter > 1) && ((element == 'P') || (element == 'E')))
		return (ft_printf(ERROR_MESSSAGE_08), false);
	return (true);
}

int	get_collectibles_left(s_game game)
{
	int	ctibles_amount;
	int	y;
	int	x;

	ctibles_amount = 0;
	y = 0;
	x = 0;
	while (y < game.max_lines)
	{
		x = 0;
		while (x < game.max_columns)
		{
			if (game.content[y][x] == COLLECTIBLE)
			{
				ctibles_amount++;
			}
			x++;
		}
		y++;
	}
	return (ctibles_amount);
}

// Copie de la map pour eviter de mettre de changer quoi ce que soit sur la map d'origine ✅
// game_copy.content = NULL; car je ne peux pas return NULL
// Calloc toutes les lignes car on utilise pas GNL cette fois (sinon segfault) ✅
s_game	duplicate_game(s_game game)
{
	s_game	game_copy;
	int		y;

	game_copy.max_columns = game.max_columns;
	game_copy.max_lines = game.max_lines;
	game_copy.content = ft_calloc(game.max_lines, sizeof(char *));
	if (!game_copy.content)
		game_copy.content = NULL;
	y = 0;
	while (y < game.max_lines)
	{
		game_copy.content[y] = ft_calloc(game.max_columns, sizeof(char));
		if (!game_copy.content[y])
			game_copy.content = NULL;
		game_copy.content[y] = ft_memcpy(game_copy.content[y], game.content[y],
				(size_t)game.max_columns);
		y++;
	}
	return (game_copy);
}

four_moves	moves_options_set_up(tile player_pos)
{
	four_moves	player_go;

	player_go.up.line = PLAYER_LINE - 1;
	player_go.up.column = PLAYER_COLUMN;
	player_go.left.line = PLAYER_LINE;
	player_go.left.column = PLAYER_COLUMN - 1;
	player_go.down.line = PLAYER_LINE + 1;
	player_go.down.column = PLAYER_COLUMN;
	player_go.right.line = PLAYER_LINE;
	player_go.right.column = PLAYER_COLUMN + 1;
	return (player_go);
}

bool	path_pre_checks(s_game *game_copy, tile *player_pos)
{
	if ((PLAYER_LINE_PTR < 0) || (PLAYER_COLUMN_PTR < 0)
		|| (PLAYER_LINE_PTR > MAX_GAME_LINES)
		|| (PLAYER_COLUMN_PTR > MAX_GAME_COLUMNS))
		return (false);
	if (TILE_CHAR_PTR(game_copy->content, player_pos) == WALL)
		return (false);
	if (TILE_CHAR_PTR(game_copy->content, player_pos) == CHECKED)
		return (false);
	return (true);
}
// Step 1 : Verifie que Player est dans le rectangle
// Step 2 : Vérif si player est sur la destination (= escape/collectible)
// Step 3 : Vérif si on est sur un mur
// Step 4 : Vérif si on est deja passé sur cette case
// Step 5 : Sauvegarder visite de la case (marquer un V)
bool	is_path_valid(tile player_pos, tile dest_pos, s_game game_copy,
		int tot_ctibles)
{
	static int	ctibles_counter;
	static int	escape_found;
	four_moves	player_go;

	if (!path_pre_checks(&game_copy, &player_pos))
		return (false);
	if (TILE_CHAR(game_copy.content, player_pos) == COLLECTIBLE)
		ctibles_counter++;
	if (PLAYER_LINE == dest_pos.line && (PLAYER_COLUMN == dest_pos.column))
		escape_found = 1;
	TILE_CHAR(game_copy.content, player_pos) = CHECKED;
	if ((ctibles_counter == tot_ctibles) && (escape_found == 1))
		return (true);
	player_go = moves_options_set_up(player_pos);
	if (is_path_valid(player_go.up, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.left, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.down, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.right, dest_pos, game_copy, tot_ctibles))
		return (true);
	return (false);
}
