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

#ifndef SO_LONG_H
# define SO_LONG_H

// ⚪ #define - Yeah that's a lot, don't judge me.
# define PATH_GROUND "./4_So_Long/ic_Square_Purple.png" // ‼️Ne marche que via mon VSCode - Trouver une autre solution
# define PATH_WALL "./4_So_Long/ic_Square_Black.png"	// En attendant, run Valgrind depuis 00_VSCode et mettre chemin d'accès :
# define PATH_PLAYER "./4_So_Long/ic_Player_Diplo.png"	// valgrind ./4_So_Long/so_long /home/sophie/Documents/00_VS_Code/4_So_Long/mapSI.ber
# define PATH_COLLECTIBLE "./4_So_Long/ic_Collectible_Corn.png"
# define PATH_ESCAPE "./4_So_Long/ic_Escape_Bike.png"
# define RIGHT 6
# define LEFT 4
# define UP 8
# define DOWN 2
# define TILE_CHAR(MAP, ELEMENT) (MAP)[(ELEMENT).line][(ELEMENT).column]
# define TILE_CHAR_PTR(MAP, ELEMENT) (MAP)[(ELEMENT)->line][(ELEMENT)->column]
# define PLAYER_POSITION game.content[player.line][player.column]
# define PLAYER_LINE player_pos.line
# define PLAYER_LINE_PTR player_pos->line
# define PLAYER_COLUMN player_pos.column
# define PLAYER_COLUMN_PTR player_pos->column
# define MAX_GAME_LINES game_copy->max_lines
# define MAX_GAME_COLUMNS game_copy->max_columns
# define TARGET game.content[target.line][target.column]
# define WINDOW game->window

# define PLAYER_IMG game->player_image
# define COLLECTIBLE_IMG game->collectible_image
# define ESCAPE_IMG game->escape_image
# define WALL_IMG game->wall_image

# define P_IMG_INSTANCE PLAYER_IMG->instances
# define C_IMG_INSTANCE game->collectible_image->instances
# define E_IMG_INSTANCE ESCAPE_IMG->instances

// # define EMOJI_PLAYER "🦕"
// # define EMOJI_COLLECTIBLE "🌽"
// # define EMOJI_ESCAPE "🛴"
// # define EMOJI_WALL "🟩"
// # define EMOJI_GROUND "⬛"
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define ESCAPE 'E'
# define EMPTY_SPACE '0'
# define CHECKED 'V'

# define GAME_NAME "Space Invader Diplo Corn Quest"

# define OK_MESSSAGE_01 "Check up 1/2 done - Logic part is about to be free\n"
# define OK_MESSSAGE_02 "Check up 2/2 done - You're good to play - Have fun !\n"
# define OK_MESSSAGE_03 "Did you just dare press the escape key? Coward.\n"
# define OK_MESSSAGE_05 "\nAnd ... Time to say goodbye !\n"

# define ERROR_MESSSAGE_01 "No map, no play !"
# define ERROR_MESSSAGE_02 "Map file extension must be .ber"
# define ERROR_MESSSAGE_03 "Error : [Map empty or not displayable]\n"
# define ERROR_MESSSAGE_04 "Error : [Your funky map isn't valid, make sure there are walls all around !]\n"
# define ERROR_MESSSAGE_05 "Error : [Your artistic map isn't valid, please make it rectangular !]\n"
# define ERROR_MESSSAGE_06 "Error : [Map too small, no space to play :( ]\n"
# define ERROR_MESSSAGE_07 "Error : [Something is missing - Pick & Choose : Player / Collectible / Exit]\n"
# define ERROR_MESSSAGE_08 "Error : [Too many ... - Pick & Choose : Players / Escapes]\n"
# define ERROR_MESSSAGE_09 "Error : [Looks like some elements can't be reached - Check the walls position !]\n"
# define ERROR_MESSSAGE_10 "Error : [Something went wrong with an image display]\n"

# define TILE_SIZE 72

// ⚪ #include
# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>	// pour errno right below
# include <errno.h>

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>

// NOTE : mettre les dossiers 99 + 98 au lieu de ca ^ car ce projet dépend des .h + .a mais pas besoin du reste

// ⚪ Structs
typedef struct node
{
	int			line;
	int			column;
}				tile;

typedef struct four_moves
{
	tile		up;
	tile		left;
	tile		down;
	tile		right;
}				four_moves;

typedef struct
{
	int			max_lines;
	int			max_columns;
	char		**content;
	tile		escape_pos;
	mlx_t		*window;
	mlx_image_t	*ground_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*player_image;
	mlx_image_t	*collectible_image;
	mlx_image_t	*escape_image;
	mlx_image_t	*bonus_string1;
	mlx_image_t	*bonus_string2;
}				s_game;

// ⚪ Pre launch check functions
int				check_input_get_fd(char *path);
void			get_map_size(int fd, s_game *game);
void			set_structs_pointers_to_null(s_game *game);
bool			check_everything(s_game *game);
bool			are_walls_approved(s_game game);
bool			is_path_valid(tile player_pos, tile dest_pos, s_game game_copy, int tot_ctibles);
bool			path_pre_checks(s_game *game_copy, tile *player_pos);
four_moves		moves_options_set_up(tile player_pos);
bool			is_element(s_game *game, char element);
s_game			duplicate_game(s_game game);

// ⚪ Helpers
tile			get_tile_position(s_game game, char element);
tile			target_position(s_game game, int move);
bool			is_move_allowed(s_game game, tile target);
void			move_player_logic(s_game game, int move);
void			move_player_graphic(s_game *game);
int				get_collectibles_left(s_game game);
void			delete_collectible_instance(s_game *game);

// ⚪ MLX Helpers
s_game			build_map(int fd, char *path);
mlx_image_t		*path_to_image(s_game *game, mlx_t *game_window, char *path);
void			display_image(s_game *game, mlx_image_t *image, int column, int line);
void			display_map(s_game *game);
void			add_1CE_images(s_game *game);
void			add_P_image(s_game *game);
void			key_actions(mlx_key_data_t keydata, void *param);
void			bonus_counter(s_game game, int step_counter);

// ⚪ Clean up functions - So sort / merge / check / set up / delete
void			simple_print_exit(char *s);
void			free_logic_part(char *message, s_game *any_game);
void			free_gnl_return_and_exit(char *error_message, char **line, int *fd);
void			clean_and_exit(void *param);

// ⚪ Testing
void	print_map_fun(s_game game); // To delete - Only for testing
#endif
