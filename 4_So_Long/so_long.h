/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/21 12:19:33 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// ⚪ #define - Yeah that's a lot, don't judge me.
// ‼️Paths ne marchent que via mon VSCode - Trouver une autre solution
// En attendant, run Valgrind depuis 00_VSCode et mettre le chemin d'accès
// valgrind ./4_So_Long/so_long /home/sophie/Documents/__path__de__la__map
# define PATH_GROUND "./4_So_Long/ic_Square_Purple.png"
# define PATH_WALL "./4_So_Long/ic_Square_Black.png"
# define PATH_PLAYER "./4_So_Long/ic_Player_Diplo.png"
# define PATH_COLLECTIBLE "./4_So_Long/ic_Collectible_Corn.png"
# define PATH_ESCAPE "./4_So_Long/ic_Escape_Bike.png"
# define RIGHT 6
# define LEFT 4
# define UP 8
# define DOWN 2
# define TILE_CHAR(MAP, ELEMENT) (MAP)[(ELEMENT).line][(ELEMENT).column]
# define TILE_CHAR_PTR(MAP, ELEMENT) (MAP)[(ELEMENT)->line][(ELEMENT)->column]

# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define ESCAPE 'E'
# define EMPTY_SPACE '0'
# define CHECKED 'V'

# define GAME_NAME "Space Invader Diplo Corn Quest"

# define MSG_01 "Check up 1/2 done - Logic part is about to be free\n"
# define MSG_02 "Check up 2/2 done - You're good to play - Have fun !\n"
# define MSG_03 "Did you just dare press the escape key? Coward.\n"
# define MSG_04 "\nAnd ... Tiiime tooo say goodbye !\n"

# define ERR_MSG_01 "No map, no play !"
# define ERR_MSG_02 "Map file extension must be .ber"
# define ERR_MSG_03 "Map empty or not displayable"
# define ERR_MSG_04 "Your funky map is not valid, check the walls position !"
# define ERR_MSG_05 "Your artistic map isn't valid, it has to be rectangular !"
# define ERR_MSG_06 "Map too small, no space to play :( "
# define ERR_MSG_07 "Something is missing (Player / Collectible / Exit)"
# define ERR_MSG_08 "Too many ... - Pick & Choose : Players / Escapes"
# define ERR_MSG_09 "Error : [Looks like some elements can't be reached !]\n"
# define ERR_MSG_10 "Something went wrong with an image display"

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
}				t_tile;

typedef struct moves
{
	t_tile		up;
	t_tile		left;
	t_tile		down;
	t_tile		right;
}				t_four_moves;

typedef struct
{
	int			max_lines;
	int			max_columns;
	char		**content;
	t_tile		escape_pos;
	mlx_t		*window;
	mlx_image_t	*ground_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*player_image;
	mlx_image_t	*collectible_image;
	mlx_image_t	*escape_image;
	mlx_image_t	*bonus_string1;
	mlx_image_t	*bonus_string2;
}				t_game;

// ⚪ Pre launch check functions
int				check_input_get_fd(char *path);
void			get_map_size(int fd, t_game *game);
void			set_structs_pointers_to_null(t_game *game);
bool			check_everything(t_game *game);
bool			are_walls_approved(t_game game);
bool			is_path_valid(t_tile player_pos, t_tile dest_pos, t_game game_copy,
					int tot_ctibles);
bool			path_pre_checks(t_game *game_copy, t_tile *player_pos);
t_four_moves		moves_options_set_up(t_tile player_pos);
bool			is_element(t_game *game, char element);
t_game			duplicate_game(t_game game);

// ⚪ Helpers
t_tile			get_tile_position(t_game game, char element);
t_tile			target_position(t_game game, int move);
bool			is_move_allowed(t_game game, t_tile target);
void			move_player_logic(t_game game, int move);
void			move_player_graphic(t_game *game);
int				get_collectibles_left(t_game game);
void			delete_collectible_instance(t_game *game);

// ⚪ MLX Helpers
t_game			build_map(int fd, char *path);
mlx_image_t		*path_to_image(t_game *game, mlx_t *game_window, char *path);
void			display_image(t_game *game, mlx_image_t *image, int column,
					int line);
void			display_map(t_game *game);
void			add_wall_collectible_exit_images(t_game *game);
void			add_player_image(t_game *game);
void			key_actions(mlx_key_data_t keydata, void *param);
void			bonus_counter(t_game game, int step_counter);

// ⚪ Clean up functions - So sort / merge / check / set up / delete
void			simple_print_exit(char *s);
void			free_logic_part(char *message, t_game *any_game);
void			free_gnl_return_and_exit(char *error_message, char **line,
					int *fd);
void			clean_and_exit(void *param);

// ⚪ Testing
void	print_map_fun(t_game game); // To delete - Only for testing
#endif
