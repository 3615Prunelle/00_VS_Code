/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:25:52 by schappuy          #+#    #+#             */
/*   Updated: 2025/03/22 00:10:39 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Exactly the same as get_next_line.c ?
//Just the main?

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*path_to_file;
	int		file_descriptor;
	char	*line;
	int		line_number;
	int		i;

	i = 0;
	line_number = 1;

//tableau de variables statiques ?
//Adresse d'un buffer dans chaque element du tableau
//mettre fd en parametre
//plusieurs buffers en variables statiques

	int multiple_fd = {1, 2, 3};

	while (i < 10)
	{
		scanf ("%s", path_to_file);
		multiple_fd[&i] = open (path_to_file, O_RDONLY);
		i++;
	}

	line = ft_calloc(1, 1);

	i = 0;
	while (i < 10)
	{
		while (TBD)
		{
			line = get_next_line(multiple_fd[i]);
			printf ("[Line %i of FD %i]	%s", line_number, file_descriptor, line);
			line_number++;
		}
	}
	while (line != (NULL))
	{

	}
	free(line);

	return (0);
}
