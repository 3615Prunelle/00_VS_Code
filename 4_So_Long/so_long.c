#include "so_long.h"

char		**so_long(int	fd)
{
	game		my_game;											// Solution badass pour passer toutes les infos en meme temps (FAB 4 PRESIDENT)
	char		*line_by_line;										// map[0] me donnait des segfaults donc je procede avec char *
	int			length_line;
// -------------------------------------------------------------------------------------------------------------------- Deal with the map itself first / Get the size of it ✅
	line_by_line = get_next_line(fd);								// ℹ️ GNL aloue la memoire a line_by_line ✅ FREE in the loop below
	if (!line_by_line)
	{
		printf ("Error\n>> Map empty or not displayable oO\n\n");
		free_gnl_stuff(&line_by_line, &fd);
		return (NULL);									// ✅ All heap blocks were freed -- no leaks are possible
	}
	length_line = ft_strlen(line_by_line);
	int line_counter = 0;
	while (line_by_line != NULL)
	{
		free(line_by_line);								// FREE ✅
		line_by_line = get_next_line(fd);				// ℹ️ GNL aloue la memoire a line_by_line ✅ FREE right above
		line_counter++;
// -------------------------------------------------------------------------------------------------------------- Check if all lines are equal in size (= rectangular map) ✅
		if (((line_by_line != NULL)) && (ft_strlen(line_by_line) != length_line))
		{
			printf("Error\n>> Sorry, your funky map isn't valid, please make it rectangular !\n\n");
			free_gnl_stuff(&line_by_line, &fd);
			return (NULL);								// ✅ All heap blocks were freed -- no leaks are possible
		}
	}
	if ((length_line < 4) || (line_counter < 3))		// Taille minimum pour avoir autre chose que des murs
	{
		printf ("Error\n>> Map not displayable\n\n");
		free_gnl_stuff(&line_by_line, &fd);
		return (NULL);									// ✅ All heap blocks were freed -- no leaks are possible
	}
	close(fd);															// Sinon ne lira pas suite
// ------------------------------------------------------------------------------------------------------------------------------------------------ Alloc memory & fill it ✅
	my_game.content = ft_calloc((line_counter + 1), sizeof(char *));	// On alloue les lignes uniquement (colonnes done by GNL) ✅ FREE : In the last loop
	if (!my_game.content)
		return (NULL);
	fd = open(PATH, O_RDWR);
	my_game.content[0] = get_next_line(fd);
	int i = 0;
	while (my_game.content[i] != NULL)
	{
		i++;
		my_game.content[i] = get_next_line(fd);							// Memoire allouee pour chaque ligne ✅ FREE in the loop at the end of the function
	}

	my_game.max_lines = line_counter;
	my_game.max_columns = length_line;

	printf("Map to check :\n\n");
	print_map_fun(my_game);

	if (check_everything(my_game) == 0)
	{
		free_game(&my_game);
		return (NULL);											// ✅ All heap blocks were freed -- no leaks are possible
	}

	tile	player;												// Redondance évitable ? Idem pour les deux blocs suivants.
	player = is_player(my_game);

	tile	exit;
	exit = is_exit(my_game);

	int collec_left;
	collec_left = is_collec(my_game, player, false);

	printf("⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳ C'EST PARTI !! ˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	while (true)													// Condition acceptable ? Rien trouvé d'autre car on sort de la loop avec break.
	{
		collec_left = is_collec(my_game, player, true);
		print_map_fun(my_game);
		printf("\n\n");
		if (collec_left == 0 && (player.line == exit.line) && (player.column == exit.column))
		{
			printf("\n⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳ FINITO !! ˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
			break;
		}
		player = player_move(my_game, player, exit);
	}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------- Clean up ✅
	free_game(&my_game);
	return (NULL);
}

int		main(void)
{
	//mlx_init();							// Let's get the party started

	int	fd;
	fd = open(PATH, O_RDWR);				// ‼️ Trouver un moyen pour que ça n'accepte que les .ber

	if((!fd) || (fd < 0))
	{
		printf ("Error\n>> Map missing OLALA NICHT GUT\n\n");
		return (1);
	}
	so_long(fd);
	return (0);
}
