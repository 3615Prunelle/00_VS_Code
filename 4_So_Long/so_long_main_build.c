#include "so_long.h"

/* Notes random
🟡 Callbsack function = Use the amount of parameters mentionned in the .h - If need more, use struct
🟢 Hooks allow you to add your own functions to the main loop execution of the program, aka these functions get executed every frame.
🟡 image->instances[0].x/y = Déplacer une image
🟣 mlx_image_t *img = mlx_new_image(mlx, 32, 32);		= Créer une image à partir de zéro
🟣 mlx_image_t *img = mlx_texture_to_image(mlx, tex);	= Créer une image à partir d’une texture existante
🔵 Ne jamais free() ce que MLX a donné
🔵 mlx_terminate() s’occupe de free tout ce qui vient de MLX
🟠 MLX42 ne supporte qu’un seul mlx_key_hook() à la fois. ✅ Solution : tout gérer dans une seule fonction de hook.
🟠 mlx_key_hook() déclenche une action quand une touche est pressée ou relâchée.
🟠 mlx_key_hook() appelle ma fonction key_actions (faite sur la base d'une callback function : mlx_keyfun) chaque fois qu’une touche est pressée.
‼️ MLX42 NB : 2 forbidden functions mlx_put_pixel  and mlx_resize_image
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

int		main(int argc, char **argv)
{
	// mlx_t *blabla = mlx_init(1000, 1000, GAME_NAME, true);	// Use if evaluator complains about Valgrind output
	// mlx_terminate(blabla);
	// exit(1);

	char *path;
	int fd;

	if(argc == 2)
	{
		path = argv[1];
		fd = check_input_get_fd(path);					// Exit here = Valgrind OK ✅🆓

		game	my_game;
		my_game = build_map(fd, path);					// Création/Remplissage de la carte et affichage de la fenêtre de jeu (vide) + upload image player

		if (!(check_everything(&my_game)))				// Attention, on passe my_game donc une copie sera faite = aucune info ne reste
		{
			clean_and_exit(&my_game);					// free_game_content ne va pas car MLX a malloc l'image du player dans build_map
		}

		display_map(&my_game);							// Set up de l'affichage de la carte (real display dans mlx_loop)

		// Hook = Set up de fonction qui sera appelée par mlx_loop
		mlx_key_hook(my_game.window, key_actions, &my_game);					// Seule fonction pour interagir avec le jeu : key_actions
	// ------------------------------------------------------------------------- Quit in a clean way when clic on cross. Check if MEM LEAKS ‼️
		mlx_close_hook(my_game.window, clean_and_exit, &my_game);
		ft_printf(OK_MESSSAGE_02);
		mlx_loop(my_game.window);		// ‼️Keep at the end - Starts to render to window with all requested elements, until shutdown is requested
	// ----------------------------------------------------------------------------------------------------------------------------------- Clean up ✅
		clean_and_exit(&my_game);			// In case ESC pressed or if everything goes correctly and the exit is naturally happening when all collectibles are reached ?
	}
	else if(argc < 2)
		ft_printf(ERROR_MESSSAGE_01);

	return(0);
}
int		check_input_get_fd(char *path)
{
	int size_path = ft_strlen(path);
	char *extension = ft_substr(path, (size_path - 4), size_path);	// 🆓 Calloc done pour *extension
	char *compare;
	compare = ft_strdup(".ber");

	if (ft_strncmp (extension, compare, 5) != 0)					// 🆓 Malloc done on strdup
	{
		free(extension);
		free(compare);
		ft_printf (ERROR_MESSSAGE_02);	// Ou utiliser strerror & perror ?
		exit (1);													// Exit here = Valgrind OK ✅🆓
	}
	free(extension);
	free(compare);

	int	fd;
	fd = open(path, O_RDWR);

	if((!fd) || (fd < 0))
	{
		ft_printf (ERROR_MESSSAGE_01);
		exit (1);													// Exit here = Valgrind OK ✅🆓
	}
	return(fd);
}
void	set_structs_pointers_to_null(game *my_game)
{
	my_game->ground_image = NULL;		// Pour éviter valeurs poubelle et segfaults quand passage dans free_game_content
	my_game->wall_image = NULL;
	my_game->player_image = NULL;
	my_game->collectible_image = NULL;
	my_game->escape_image = NULL;
	my_game->bonus_string1 = NULL;
	my_game->bonus_string2 = NULL;
	my_game->window = NULL;
}
void	get_map_size(int fd, game *my_game)
{
	char		*gnl_line_return;
	size_t		length_line;

	int line_counter;
	line_counter = 0;

	gnl_line_return = get_next_line(fd);					// Ⓜ️ GNL aloue la memoire a gnl_line_return
	if (!gnl_line_return)
		free_gnl_return_and_exit(ERROR_MESSSAGE_03, &gnl_line_return, &fd);	// Exit here = Valgrind OK ✅🆓
	length_line = ft_strlen(gnl_line_return);

	while (gnl_line_return != NULL)
	{
		free(gnl_line_return);
		gnl_line_return = get_next_line(fd);				// Ⓜ️ GNL aloue la memoire a gnl_line_return ✅ FREE right above
		line_counter++;
		if ((gnl_line_return != NULL) && (ft_strlen(gnl_line_return) != length_line))	// Are all lines are equal in size (= rectangular map)
			free_gnl_return_and_exit(ERROR_MESSSAGE_05, &gnl_line_return, &fd);			// Exit here = Valgrind OK ✅🆓
	}
	if ((length_line < 4) || (line_counter < 3))	// Taille minimum pour avoir autre chose que des murs (not requested in subject)
		free_gnl_return_and_exit(ERROR_MESSSAGE_06, &gnl_line_return, &fd);	// Exit here = Valgrind OK ✅🆓
	my_game->max_lines = line_counter;
	my_game->max_columns = length_line;
	close(fd);										// Sinon ne lira pas suite
}

void		simple_print_exit(char *s)
{
	// if things get too spicy, add a call to the other clean up functions ?
	ft_printf("Error : [%s]\n", s);
	exit(1);
}

game	build_map(int fd, char *path)
{
	game		my_game;

	get_map_size(fd, &my_game);
	// ---------------------------------------------------------------------------------------------- Alloc memory & fill it ✅
	my_game.content = ft_calloc((my_game.max_lines + 1), sizeof(char *));	// On alloue la première colonne uniquement (lignes done by GNL) ✅ FREE dans la fonction appelante (main)
	if (!my_game.content)
		simple_print_exit(strerror(errno));	// Exit here = Valgrind OK ✅🆓
	fd = open(path, O_RDWR);
	my_game.content[0] = get_next_line(fd);
	int i = 0;
	while (my_game.content[i] != NULL)
	{
		i++;
		my_game.content[i] = get_next_line(fd);			// Memoire allouee pour chaque ligne ✅ FREE dans la fonction appelante (main)
	}

	my_game.escape_position = get_tile_position(my_game, ESCAPE);
	set_structs_pointers_to_null(&my_game);

	if(!(my_game.window = mlx_init(TILE_SIZE*(my_game.max_columns-1), TILE_SIZE*my_game.max_lines, GAME_NAME, false)))	// Connection to the graphical system - MLX MALLOC DONE HERE ‼️
	{ // still reachable: 299,966 bytes in 3,312 blocks - Investigated and normal, check if increase after
		clean_and_exit(&my_game);	// Valgrind ❌ but normal (internal MLX42/GLFW allocation, can't be freed manually)
	}
	my_game.player_image = path_to_image(&my_game, my_game.window, PATH_PLAYER);
	return (my_game);
}
