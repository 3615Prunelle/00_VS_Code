/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/23 14:39:33 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Name of new library defined here (so we can use #include "current_ft.h")
#ifndef SO_LONG_H
# define SO_LONG_H

// All #define can be placed only here
# define PATH "4_So_Long/S_I_map.txt"
# define RIGHT 6 // !! Change that before eval, so the keys are the same as requested in the subject
# define LEFT 4
# define UP 8
# define DOWN 2
# define PLAYER_POSITION map[player.line][player.column]
# define TARGET_POSITION map[target.line][target.column]
# define EXIT_POSITION map[exit.line][exit.column]
# define MAP_SIZE map[max.line][max.column]
# define PLA "🦕"
# define COL "🌽"
# define EXI "🛴"
# define WAL "🟩"
# define EMP "⬛"

// All #include only here (if #include "current_ft.h" is in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

//Include from other projects
#include "/home/schappuy/00_VS_Code/3_Get_Next_Line/get_next_line.h"
#include "/home/schappuy/00_VS_Code/1_Libft/libft.h"
// mettre les.h ici + ajouter les functions.c au tasks.json

typedef struct GPS
{
	int line;
	int column;
} position;

// Main Function
char		**so_long(int fd);

// Helpers
position	player_move(char **map, position player, position exit, int lines);
position	check_target(char **map, position player, position target);
position	is_player(char **map, int lines);
int			is_collec(char **map, int lines, bool in_loop);
int			is_exit(char **map, int lines, position *exit);
void		freeee(void **address_of_anything);
void		print_map(char **map, int lines);
void		print_map_fun(char **map, int lines, int col);

// trouver un equivalent a :	char		*free_null_three(char **buff, char **line, char **temp);

#endif
