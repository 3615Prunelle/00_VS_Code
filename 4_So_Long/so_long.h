/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/05/12 20:20:14 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ⚪ Name of new library defined here (so we can use #include "current_ft.h")
#ifndef SO_LONG_H
# define SO_LONG_H

// ⚪ All #define can be placed only here
# define PATH "./4_So_Long/S_I_map.ber"
# define RIGHT	6									// !! Change that before eval, so the keys are the same as requested in the subject
# define LEFT	4
# define UP		8
# define DOWN	2
# define GET_TILE(MAP, ELEMENT)		(MAP)[(ELEMENT).line][(ELEMENT).column] // remplace tous les autres - Penser a update
# define PLAYER_POSITION			my_game->content[player.line][player.column]
# define TARGET_POSITION			my_game->content[target.line][target.column]
# define ESCAPE_POSITION			my_game->content[my_game->escape_position.line][my_game->escape_position.column]
# define MAP_SIZE					my_game->content[my_game->max_lines][my_game->max_columns]
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

// ⚪ MLX42 related #define
# define TILE_SIZE 72

// ⚪ All #include only here (put #include "current_ft.h" is in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include <MLX42/MLX42.h>			// To use MLX42

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ ‼️ ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json
#include "../1_Libft/libft.h"
#include "../2_ft_printf/ft_printf.h"
#include "../3_Get_Next_Line/get_next_line.h"

// ⚪ Non-MLX42 structs
typedef struct node
{
	int		line;
	int		column;
} tile;

typedef struct game
{
	int			max_lines;
	int			max_columns;
	int			counter;
	char		**content;
	tile		escape_position;
	mlx_t		*window;
	mlx_image_t	*player_image;
	mlx_image_t	*collectible_image;
	mlx_image_t	*escape_image;
} game;

// ⚪ My MLX42 structs
typedef struct mic_mac		// Struct to pass many arguments to a function that can't be called twice or can only take a limited amount of arguments
{
	mlx_t			*window;
	/* Add all the stuff to free mlx + not-mlx part (in main + all the other functions) */
	mlx_texture_t	*player_texture;
	mlx_texture_t	*collec_texture;
	mlx_texture_t	*escape_texture;
	mlx_texture_t	*ground_texture;
	mlx_texture_t	*wall_texture;
	mlx_image_t		*player_image;
	mlx_image_t		*wall_image;
	// game	my_game;								// ‼️‼️‼️ Uncomment when previous code is connected to the MLX42 part
	// anything else added here needs to be added everywhere (initialised where needed + added in the free function)

} all_mallocs;

// ⚪ Helpers
bool	player_move(game *my_game, int move);
bool	check_target(game *my_game, tile player_position, tile target);
tile	element_position(game my_game, char element, int *counter);
tile	target_position(game *my_game, int move);	// MERGE
tile	is_player(game my_game);					// MERGE
tile	is_escape(game my_game);					// MERGE

int		check_everything(game my_game);	// KEEP
int		check_walls(game my_game);		// KEEP
int		get_collectibles_left(game my_game, bool in_game);

game	duplicate_game(game my_game);				// Maybe not needed, check when all the rest is sorted (and before dealing with memory)
bool	is_path_valid(tile player_position, tile destination_position, game my_game_copy, int *total_collectibles);

void	free_game(game *any);
void	free_gnl_stuff(char **line, int *fd);
void	print_map(game my_game);					// To delete
void	print_map_fun(game my_game);				// To delete - Only for testing

// ⚪ MLX Helpers
game			build_map(char *path);
mlx_image_t		*path_to_image(mlx_t *game_window, char *path);
void			display_image(mlx_t *game_window, mlx_image_t *image, int colonne, int ligne);
void			display_map(game *my_game);
void			key_actions(mlx_key_data_t keydata, void *param);
void			free_before_exit(void *param); // model = mlx_closefunc
void			ft_free_exit(all_mallocs *free_this);

#endif
