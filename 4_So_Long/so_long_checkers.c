/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:27 by sophie            #+#    #+#             */
/*   Updated: 2025/08/21 14:23:00 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Je passe un pointeur en param pour libérer la mémoire dans
// fonctions appelées si erreurs (gain de place norminette)
// 1st if : Check if walls all around ✅
// 2nd if : Check if all elements are here in the correct amount ✅
// game_copy pour ne pas dupliquer le jeu a chaque recursion dans path_valid
bool	check_everything(t_game *game)
{
	t_tile	player_pos;
	int		ctibles_amount;
	t_game	game_copy;

	if (!are_walls_approved(*game))
	{
		ft_printf("Error : [%s]\n", ERR_MSG_04);
		return (false);
	}
	if ((!is_element(game, PLAYER)) || (!is_element(game, ESCAPE))
		|| (!is_element(game, COLLEC)))
	{
		return (false);
	}
	player_pos = get_tile_position(*game, PLAYER);
	ctibles_amount = get_collectibles_left(*game);
	game->escape_pos = get_tile_position(*game, ESCAPE);
	game_copy = duplicate_game(*game);
	if (!is_path_valid(player_pos, game->escape_pos, game_copy, ctibles_amount))
	{
		free_logic_part(ERR_MSG_09, &game_copy);
		return (false);
	}
	free_logic_part(MSG_01, &game_copy);
	return (true);
}

// Step 1 : Verif de la 1ere & derniere ligne
// Step 2 : Verif des lignes in between
bool	are_walls_approved(t_game game)
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
t_tile	get_tile_position(t_game game, char element)
{
	int		y;
	int		x;
	t_tile	element_position;

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
bool	is_element(t_game *game, char element)
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
		return (ft_printf("Error : [%s]\n", ERR_MSG_07), false);
	if ((element_counter > 1) && ((element == 'P') || (element == 'E')))
		return (ft_printf("Error : [%s]\n", ERR_MSG_08), false);
	return (true);
}

int	get_collectibles_left(t_game game)
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
			if (game.content[y][x] == COLLEC)
			{
				ctibles_amount++;
			}
			x++;
		}
		y++;
	}
	return (ctibles_amount);
}
