/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:21:43 by schappuy          #+#    #+#             */
/*   Updated: 2025/03/31 19:08:23 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*buffer_array[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!buffer_array[fd])
	{
		buffer_array[fd] = ft_calloc (BUFFER_SIZE + 1, 1);
		read (fd, buffer_array[fd], BUFFER_SIZE);
	}
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	line = ft_calloc(BUFFER_SIZE + 1, 1);
	read_line(fd, &buffer_array[fd], &line, &temp);
	free(temp);

	return (line);
}

void	read_line(int fd, char **buffer, char **line, char **temp)
{
	while (*buffer)
	{
		if (n_counter(*buffer))
		{
			*temp = ft_strlcpy(*temp, *buffer,
					newline_index_check(*buffer) + 1);
			*line = ft_strjoin_bis(*line, *temp);
			*buffer = ft_strlcpy(*buffer, ft_strchr(*buffer, '\n'),
					ft_strlen(*buffer) - newline_index_check(*buffer) + 1);
			break ;
		}
		*line = ft_strjoin_bis(*line, *buffer);
		ft_memset(*buffer, 0, BUFFER_SIZE);
		if (read(fd, *buffer, BUFFER_SIZE) <= 0)
		{
			if (*line[0] == '\0')
			{
				free(*line);
				*line = NULL;
			}
			break ;
		}
	}
}

void	*ft_memset(void *str, int constante, size_t taille)
{
	unsigned char	*ptr_s;
	size_t			i;

	ptr_s = (unsigned char *)str;
	i = 0;
	while (i < taille)
	{
		ptr_s[i] = (unsigned char)constante;
		i++;
	}
	return (str);
}

int	n_counter(char *buffer)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			counter++;
		i++;
	}
	return (counter);
}

int	newline_index_check(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

//#define ROUQUINETTE_DEBUG //pour lancer tester : comment out uniquement cette ligne au lieu de tout le reste en dessous
#ifdef ROUQUINETTE_DEBUG

void freedom_yolo(void **mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

int	main(void)
{
	const char	*path_to_file1;
	const char	*path_to_file2;
	const char	*path_to_file3;
	int			file_descriptor[3];
	int			fd_number;
	int			line_number;
	char		*grand_final;
//ATTENTION _ Chemin d'accès différent selon si je suis au campus ou @home
	//path_to_file = "Invalid File Descriptor";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/empty";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/41_no_nl";
	//path_to_file1 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/41_with_nl"; //HOME PATH
	//path_to_file1 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/41_with_nl"; //SCHOOL PATH
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/42_no_nl";
	//path_to_file2 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/42_with_nl"; //HOME PATH
	//path_to_file2 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/42_with_nl"; //SCHOOL PATH
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/43_no_nl";
	//path_to_file3 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/43_with_nl"; //HOME PATH
	//path_to_file3 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/43_with_nl"; //SCHOOL PATH
	path_to_file1 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_nlx5";
	path_to_file2 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_with_nl";
	path_to_file3 = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_with_nl";

	file_descriptor[0] = open (path_to_file1, O_RDONLY);
	file_descriptor[1] = open (path_to_file2, O_RDONLY);
	file_descriptor[2] = open (path_to_file3, O_RDONLY);

	line_number = 1;
	fd_number = 1;
	grand_final = ft_calloc(1, 1);

	while (grand_final != (NULL))
	{
		while (fd_number <= 3) // 3 = nombre de fichiers a lire - Trouver un autre moyen moin bancal de rentrer dans la boucle
		{
			freedom_yolo ((void **)&grand_final);
			grand_final = get_next_line(file_descriptor[fd_number - 1]);
			if (grand_final == NULL)
				break ;
			printf ("| File : [%i] - Line : [%i] |	%s", fd_number, line_number, grand_final);
			fd_number++;
		}
		if (!grand_final)
		{
			printf ("\n______________________ Last line reached [OR] Line not found ______________________\n\n");
			get_next_line(-1);//pour repasser une fois de + dans GNL avec (fd negatif) et free les buffers
		}
		line_number++;
		fd_number = 1;
		printf ("\n\n"); //pour separer visuellement chaque bloc de lignes
	}
	freedom_yolo((void **)&grand_final);
	return (0);
}

#endif
