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

// ⚪ Name of new library defined here (so we can use #include "current_project.h" header)
#ifndef SO_LONG_H
# define SO_LONG_H

// ⚪ #define
# define PATH_GROUND "./4_So_Long/ic_Square_Purple.png"
# define PATH_WALL "./4_So_Long/ic_Square_Black.png"
# define PATH_PLAYER "./4_So_Long/ic_Player_Diplo.png"
# define PATH_COLLECTIBLE "./4_So_Long/ic_Collectible_Corn.png"
# define PATH_ESCAPE "./4_So_Long/ic_Escape_Bike.png"
# define RIGHT	6
# define LEFT	4
# define UP		8
# define DOWN	2
# define TILE_CHAR(MAP, ELEMENT)		(MAP)[(ELEMENT).line][(ELEMENT).column] // Donne le char présent sur une tile (ou le modifie)
# define PLAYER_POSITION			my_game.content[player.line][player.column]
# define TARGET_POSITION			my_game.content[target.line][target.column]
# define ESCAPE_POSITION			my_game.content[my_game.escape_position.line][my_game.escape_position.column]
# define EMOJI_PLAYER		"🦕"
# define EMOJI_COLLECTIBLE	"🌽"
# define EMOJI_ESCAPE		"🛴"
# define EMOJI_WALL			"🟩"
# define EMOJI_GROUND		"⬛"
# define WALL			'1'
# define PLAYER			'P'
# define COLLECTIBLE	'C'
# define ESCAPE			'E'
# define EMPTY_SPACE	'0'
# define CHECKED		'V'

# define GAME_NAME	"Space Invader Diplo Corn Quest"

# define OK_MESSSAGE_01	"Non graphical check up done\n"
# define OK_MESSSAGE_02	"Graphical check up done. You're good to play - Have fun !\n"
# define OK_MESSSAGE_03	"Exit through escape key\n"
# define OK_MESSSAGE_04	"Game content is free\n"
# define OK_MESSSAGE_05	"About to pass in free_game_content before final exit\n"
# define OK_MESSSAGE_06	"Full clean done, about to exit\n"

# define ERROR_MESSSAGE_01	"Error\nMap missing OLALA NICHT GUT\n"
# define ERROR_MESSSAGE_02	"Error\nMap file extension must be .ber\n"
# define ERROR_MESSSAGE_03	"Error\nMap empty or not displayable\n"
# define ERROR_MESSSAGE_04	"Error\nYour funky map isn't valid, make sure there are walls all around !\n"
# define ERROR_MESSSAGE_05	"Error\nYour funky map isn't valid, please make it rectangular !\n"
# define ERROR_MESSSAGE_06	"Error\nMap too small, no space to play :(\n"
# define ERROR_MESSSAGE_07	"Error\nSomething is missing - Pick & Choose : Player / Collectible / Exit\n"
# define ERROR_MESSSAGE_08	"Error\nToo many ... - Pick & Choose : Players / Escapes\n"
# define ERROR_MESSSAGE_09	"Error\nLooks like some elements can't be reached - Check the walls position !\n"
# define ERROR_MESSSAGE_10	"Error in the window allocation\n"
# define ERROR_MESSSAGE_11	"Error in an image display\n"

# define TILE_SIZE 72

// ⚪ #include (don't forget to put #include "current_project.h" in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
//# include <string.h>
//# include <errno.h> ft_printf("Test errno : [%s]\n", strerror(errno));

# include <MLX42/MLX42.h>

// ⚪ Include from other projects (put relative path to avoid issues from home computer or as #include<> if compiled)
// ‼️ ‼️ ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json
#include <libft.h>
#include <ft_printf.h>
#include <get_next_line.h>

// NOTE : mettre les dossiers 99 + 98 au lieu de ca ^ car ce projet dépend des .h + .a mais pas besoin du reste

// ⚪ Structs
typedef struct node
{
	int		line;
	int		column;
} tile;

typedef struct game		// Struct to pass many arguments to a function that can't be called twice or can only take a limited amount of arguments
{
	int			max_lines;
	int			max_columns;
	char		**content;						// Seule ligne à free dans cette struct (le reste est à faire via delete_mlx42)
	tile		escape_position;
	/* Add all the stuff to free mlx (below) + not-mlx part (above) + Initialised where needed + Added in the free function */
	mlx_t		*window;
	mlx_image_t	*ground_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*player_image;
	mlx_image_t	*collectible_image;
	mlx_image_t	*escape_image;
	mlx_image_t	*bonus_string1;
	mlx_image_t	*bonus_string2;
} game;

// ⚪ Pre launch check functions
bool		check_everything(game my_game);
bool		are_walls_approved(game my_game);
bool		is_path_valid(tile player_position, tile destination_position, game my_game_copy, int total_collectibles);
bool		is_element(game my_game, char element);
game		duplicate_game(game my_game);				// Maybe not needed, check when all the rest is sorted (and before dealing with memory)

// ⚪ Helpers
tile		get_tile_position(game my_game, char element);
tile		target_position(game my_game, int move);
bool		is_move_allowed(game my_game, tile target);
void		player_move(game my_game, int move);
int			get_collectibles_left(game my_game);

// ⚪ MLX Helpers
game		build_map(char *path);
mlx_image_t	*path_to_image(game *my_game, mlx_t *game_window, char *path);
void		display_image(game *my_game, mlx_image_t *image, int colonne, int ligne);
void		display_map(game *my_game);
void		key_actions(mlx_key_data_t keydata, void *param);
void		bonus_counter(game my_game, int step_counter);

// ⚪ Clean up functions - So sort / merge / check / set up / delete
void		free_game_content(char *message, game *any_game, bool need_exit);		// pour free le game.content sans la partie graphique (si check_everything renvoie false)
void		free_gnl_return_and_exit(char *error_message, char **line, int *fd);
void		clean_and_exit(void *param);					// free everything et exit(1)

// ⚪ Testing
void		print_map(game my_game);					// To delete
void		print_map_fun(game my_game);				// To delete - Only for testing

#endif
