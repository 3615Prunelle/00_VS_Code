/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/05/04 19:31:47 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Name of new library defined here (so we can use #include "current_ft.h")
#ifndef SO_LONG_H
# define SO_LONG_H

// All #define can be placed only here
# define PATH "4_So_Long/test_map.txt"
# define RIGHT	6									// !! Change that before eval, so the keys are the same as requested in the subject
# define LEFT	4
# define UP		8
# define DOWN	2
# define PLAYER_POSITION			my_game.content[player.line][player.column]
# define GET_TILE(MAP, ELEMENT)		(MAP)[(ELEMENT).line][(ELEMENT).column] // remplace tous les autres - Penser a update
# define TARGET_POSITION			my_game.content[target.line][target.column]
# define EXIT_POSITION				my_game.content[exit.line][exit.column]
# define MAP_SIZE					my_game.content[my_game.max_lines][my_game.max_columns]
# define PLA "🦕"
# define COL "🌽"
# define EXI "🛴"
# define WAL "🟩"
# define EMP "⬛"

# define WALL			'1'
# define PLAYER			'P'
# define COLLECTIBLE	'C'
# define EXIT			'E'
# define EMPTY_SPACE	'0'
# define VISITAY		'V'

// All #include only here (if #include "current_ft.h" is in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include <mlx.h>			// Let's get it started with the MLX42

//Include from other projects (put relative path to avoid issues from home computer)
#include "../1_Libft/libft.h"
// #include "../2_ft_printf/ft_printf.h"		// Inutilisable, souci à résoudre
#include "../3_Get_Next_Line/get_next_line.h"

// ‼️ ‼️ ‼️ Mettre les.h ici + ‼️ Ajouter les functions.c au tasks.json

typedef struct node
{
	int		line;
	int		column;
	char	type; // delete that
} tile;

typedef struct game
{
	int		max_lines;
	int		max_columns;
	char	**content;
} game;

// Main Function
char	**so_long(int fd);

// Helpers
tile	player_move(game my_game, tile player, tile exit);
tile	check_target(game my_game, tile player, tile target);

int		check_everything(game my_game);
int		check_walls(game my_game);
tile	is_player(game my_game);
int		is_collec(game my_game, tile player, bool in_game_loop);
tile	is_exit(game my_game);

game	duplicate_game(game my_game);										// A utiliser uniquement avant chaque appel de is_path_valid
bool	is_path_valid(tile player, tile *destination, game my_game_copy, int *total_collectibles);	// Using pointer to change & save the checked condition of the tile

void	free_game(game *any);
void	free_gnl_stuff(char **line, int *fd);
void	print_map(game my_game);
void	print_map_fun(game my_game);

#endif
