#include "so_long.h"
// FREE ✅
// ‼️ Reminder : Use free or free function later
// ❔
// ▶️
char		**so_long(int	fd)
{
	char		**map;												// pointeur de pointeur = tableau a double entree
	char		*line_by_line;										//	map[0] me donnait des segfaults donc je procede avec char *
	position	max; 												// to define size of map (max y = max x)
	int			length_line;
// ------------------------- Deal with the map itself first - Step 1, get the size of it ----------------------------- //
	line_by_line = get_next_line(fd);								// ℹ️ GNL aloue la memoire a line_by_line ✅ FREE in the loop below
	length_line = ft_strlen(line_by_line);
	if (check_walls (line_by_line, length_line) == 0)
	{
		printf("Sorry, your funky map isn't valid, please make sure they're walls all around !\n");
		return (NULL);
	}
	int line_counter = 0;
	while (line_by_line != NULL)
	{
		free(line_by_line);											// FREE ✅
		line_by_line = get_next_line(fd);							// ℹ️ GNL aloue la memoire a line_by_line ✅ FREE right above
		line_counter++;
// ------------------------- Check if all lines are even (= rectangular map) ----------------------------- //
		if (((line_by_line != NULL)) && (ft_strlen(line_by_line) != length_line))
		{
			printf("Sorry, your funky map isn't valid, please make it rectangular !\n");
			return (NULL);
		}
	}
	close(fd);														// Sinon ne lira pas suite
// ------------------------- Step 2, alloc memory & fill it ----------------------------------------------------------- //
	map = ft_calloc((line_counter + 1), sizeof(char *));			// On alloue les lignes uniquement (les colonnes seront allouees par GNL) ✅ FREE : In the last loop
	if (!map)
	return (NULL);
	fd = open(PATH, O_RDWR);
	map[0] = get_next_line(fd);
	int i = 0;
	while (map[i] != NULL)
	{
		//printf("%s", map[i]);
		i++;
		map[i] = get_next_line(fd);									// Memoire allouee pour chaque ligne ✅ FREE in the loop at the end of the function
	}
	max.line = line_counter;										// Lignes
	max.column = ft_strlen(map[0]);									// Colonnes
// ------------------------- ✅ Check Player ----------------------------------- //
position	player;
player = is_player(map, max.line);
if ( (player.line == -1) && (player.column == -1))
return (NULL);
// ------------------------- ✅ Check Collectibles ----------------------------- //
int collec_left;
collec_left = is_collec(map, max.line, false);
if (collec_left == 0)
return (NULL);
// ------------------------- ✅ Check Exit ------------------------------------- //
	position	exit;
	if (is_exit(map, max.line, &exit) == 0)
		return (NULL);



	printf("⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅ Let the fun begin ! ⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n");
	while (true)													// condition acceptable ? Rien trouvé d'autre car on sort de la loop avec break.
	{
		collec_left = is_collec(map, max.line, true);
		print_map_fun(map, max.line, max.column);
		if (collec_left == 0 && (player.line == exit.line) && (player.column == exit.column))
			break;
		player = player_move(map, player, exit, max.line);
	}
	//print_map(map, max.line);
// ------------------------- Clean up ---------------------------------------------------------------------------------------------------- //
	while (line_counter >= 0)
	{
		free(map[line_counter]);									// FREE ✅
		line_counter--;
	}
	free(map);
	return (NULL);
}

int		main(void)
{
	int	fd;
	fd = open(PATH, O_RDWR);

	so_long(fd);

	return (0);
}
