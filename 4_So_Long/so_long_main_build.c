#include "so_long.h"

/* Notes random
🔵 Si on veut qu'une struct soit MAJ en dehors d'une fonction, il faut obligatoirement passer un pointeur de
🔵 		cette struct (et vérifier que le pointeur est passé dans tous les fonctions appelantes en amont)
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

is_ = bool
get_ = récupérer un élément ou une position
*/

int		main(int	argc, char **argv)
{
	char *path = PATH_MAP;									// changer pour argv[1] when done

	game	my_game;
	my_game = build_map(path);								// Création/Remplissage de la carte et affichage de la fenêtre de jeu (vide) + upload image player

	if (!(check_everything(my_game)))						// Attention, on passe my_game donc une copie sera faite = aucune info ne reste
	{
		clean_and_exit(&my_game);							// free_game_content ne va pas car MLX a malloc l'image du player dans build_map
	}

	display_map(&my_game);												// Set up de l'affichage de la carte (real display dans mlx_loop)

	// Hook = Set up de fonction qui sera appelée par mlx_loop
	mlx_key_hook(my_game.window, key_actions, &my_game);					// Seule fonction pour interagir avec le jeu : key_actions
// ------------------------------------------------------------------------- Quit in a clean way when clic on cross. Check if MEM LEAKS ‼️
	mlx_close_hook(my_game.window, clean_and_exit, &my_game);

	ft_printf(OK_MESSSAGE_4);
	mlx_loop(my_game.window);		// ‼️Keep at the end - Starts to render to window with all requested elements, until shutdown is requested
// ----------------------------------------------------------------------------------------------------------------------------------- Clean up ✅
	clean_and_exit(&my_game);			// In case ESC pressed or if everything goes correctly and the exit is naturally happening when all collectibles are reached ?
	return(0);
}

// ------------------------------------------------------- Game checklist - Create the required structure to store all the necessary information ✅
game	build_map(char *path)
{
	game		my_game;											// Solution badass pour passer toutes les infos en meme temps (FAB 4 PRESIDENT)
	char		*line_by_line;										// map[0] me donnait des segfaults donc je procede avec char *
	size_t		length_line;
// --------------------------------------------------------------------------------------------------------------------- Only .ber maps + Open FD ✅
	int size_path = ft_strlen(path);
	char *extension = ft_substr(path, (size_path - 4), size_path);	// 🆓 Calloc done pour *extension
	char *compare;
	compare = ft_strdup(".ber");

	if (ft_strncmp (extension, compare, 5) != 0)					// 🆓 Malloc done on strdup
	{
		free(extension);
		free(compare);
		ft_printf (ERROR_MESSSAGE_5);	// Ou utiliser strerror & perror ?
		exit (1);													// ✅ All heap blocks were freed -- no leaks are possible
	}
	free(extension);												// ✅ Free
	free(compare);

	int	fd;
	fd = open(path, O_RDWR);

	if((!fd) || (fd < 0))
	{
		ft_printf (ERROR_MESSSAGE_6);
		exit (1);													// ✅ All heap blocks were freed -- no leaks are possible
	}
// ----------------------------------------------------------------------------------------- Deal with the map itself first / Get the size of it ✅
	line_by_line = get_next_line(fd);					// 🆓 GNL aloue la memoire a line_by_line
	if (!line_by_line)
	{
		free_gnl_return_and_exit(ERROR_MESSSAGE_7, &line_by_line, &fd);
	}// ✅ All heap blocks were freed -- no leaks are possible
	length_line = ft_strlen(line_by_line);
	int line_counter = 0;
	while (line_by_line != NULL)
	{
		free(line_by_line);								// ✅ Free
		line_by_line = get_next_line(fd);				// 🆓 GNL aloue la memoire a line_by_line ✅ FREE right above
		line_counter++;
// ------------------------------------------------------------------------------------ Check if all lines are equal in size (= rectangular map) ✅
		if (((line_by_line != NULL)) && (ft_strlen(line_by_line) != length_line))
		{
			free_gnl_return_and_exit(ERROR_MESSSAGE_8, &line_by_line, &fd);
		}// ✅ All heap blocks were freed -- no leaks are possible
	}
	if ((length_line < 4) || (line_counter < 3))	// Taille minimum pour avoir autre chose que des murs
	{
		free_gnl_return_and_exit(ERROR_MESSSAGE_9, &line_by_line, &fd);									// ✅ Free
	}// ✅ All heap blocks were freed -- no leaks are possible
	close(fd);										// Sinon ne lira pas suite
// ---------------------------------------------------------------------------------------------------------------------- Alloc memory & fill it ✅
	my_game.content = ft_calloc((line_counter + 1), sizeof(char *));	// On alloue la première colonne uniquement (lignes done by GNL) ✅ FREE dans la fonction appelante (main)
	if (!my_game.content)
		exit(1);
	fd = open(PATH_MAP, O_RDWR);
	my_game.content[0] = get_next_line(fd);
	int i = 0;
	while (my_game.content[i] != NULL)
	{
		i++;
		my_game.content[i] = get_next_line(fd);			// Memoire allouee pour chaque ligne ✅ FREE dans la fonction appelante (main)
	}

	my_game.max_lines = line_counter;
	my_game.max_columns = length_line;

	my_game.escape_position = get_tile_position(my_game, ESCAPE);

	my_game.ground_image = NULL;		// Pour éviter valeurs poubelle et segfaults quand passage dans free_game_content
	my_game.wall_image = NULL;
	my_game.player_image = NULL;
	my_game.collectible_image = NULL;
	my_game.escape_image = NULL;
	my_game.bonus_string1 = NULL;
	my_game.bonus_string2 = NULL;

	if(!(my_game.window = mlx_init(TILE_SIZE*(my_game.max_columns-1), TILE_SIZE*my_game.max_lines, OK_MESSSAGE_6, false)))	// Connection to the graphical system - MLX MALLOC DONE HERE ‼️
	{
		clean_and_exit(&my_game);	// free_game_content function not necessary (tested)
		// Note: 32 bytes definitely lost when mlx_init() fails.
		// This is an internal MLX42/GLFW allocation and can't be freed manually.
		// mlx_terminate(my_game.window); // SURTOUT PAS, car rien n'a été alloué via MLX42
	}

	my_game.player_image = path_to_image(&my_game, my_game.window, PATH_PLAYER);

	return (my_game);
}
