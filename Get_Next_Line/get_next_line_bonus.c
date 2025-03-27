/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:21:43 by schappuy          #+#    #+#             */
/*   Updated: 2025/03/23 21:47:50 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#define AMOUNT_OF_FD 3

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	static int fd_array[AMOUNT_OF_FD];
	static char *buffer_array[AMOUNT_OF_FD];

	static int i;
	if (i < AMOUNT_OF_FD)
	{
		fd_array[i] = fd; //on met un FD par case
		buffer_array[i] = buffer; //on fait correspondre un buffer pour le même index
	}
	int test = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!buffer_array[i])
	{
		buffer_array[i] = ft_calloc (BUFFER_SIZE + 1, 1);
		read (fd_array[i], buffer_array[i], BUFFER_SIZE);
	}
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	line = ft_calloc(BUFFER_SIZE + 1, 1);
	read_line(i, &fd_array[i], &buffer_array[i], &line, &temp);
	free(temp);

	i++;
	if (i == AMOUNT_OF_FD)
		i = 0;

	return (line);
}

void	read_line(int i, int fd_array[i], char *buffer_array[i], char **line, char **temp)
{
	while (*buffer_array[i])
	{
		if (n_counter(i, &buffer_array[i]))
		{
			*temp = ft_strlcpy(*temp, buffer_array[i],
					newline_index_check(buffer_array[i]) + 1);
			*line = ft_strjoin_bis(*line, *temp);
			buffer_array[i] = ft_strlcpy(buffer_array[i], ft_strchr(buffer_array[i], '\n'),
					ft_strlen(buffer_array[i]) - newline_index_check(buffer_array[i]) + 1);
			break ;
		}
		*line = ft_strjoin_bis(*line, buffer_array[i]);
		ft_memset(buffer_array[i], 0, BUFFER_SIZE);
		if (read(fd_array[i], buffer_array[i], BUFFER_SIZE) <= 0)
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

int	n_counter(int j, char *buffer_array[j])
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while ((buffer_array[j]) && i < BUFFER_SIZE)
	{
		if (*buffer_array[j] == '\n')
		{
			counter++;
		}
		*buffer_array[j]++;
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

#define ROUQUINETTE_DEBUG //comment out uniquement cette ligne au lieu de tout le reste en dessous
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
	int			file_descriptor1;
	int			file_descriptor2;
	int			file_descriptor3;
	int			line_number;
	char		*grand_final;
//ATTENTION _ Chemin d'accès différent selon si je suis au campus ou @home
	//path_to_file = "Invalid File Descriptor";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/empty";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/41_no_nl";
	path_to_file1 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/41_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/42_no_nl";
	path_to_file2 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/42_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/43_no_nl";
	path_to_file3 = "/home/sophie/Documents/00_VS_Code/Get_Next_Line/gnlTester/files/43_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_nlx5";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_with_nl";

	file_descriptor1 = open (path_to_file1, O_RDONLY);
	file_descriptor2 = open (path_to_file2, O_RDONLY);
	file_descriptor3 = open (path_to_file3, O_RDONLY);

	line_number = 1;
	grand_final = ft_calloc(1, 1);
	int i = 0;

	while ((grand_final != (NULL)) && i < 3)
	{
		freedom_yolo ((void **)&grand_final);
		grand_final = get_next_line(file_descriptor1);
		if (grand_final == NULL)
			break ;
		printf ("[FD1 - Line %i]	%s", line_number, grand_final);
		line_number++;

		freedom_yolo ((void **)&grand_final);
		grand_final = get_next_line(file_descriptor2);
		if (grand_final == NULL)
			break ;
		printf ("[FD2 - Line %i]	%s", line_number, grand_final);
		line_number++;

		freedom_yolo ((void **)&grand_final);
		grand_final = get_next_line(file_descriptor3);
		if (grand_final == NULL)
			break ;
		printf ("[FD3 - Line %i]	%s", line_number, grand_final);
		line_number++;
	}
	if (!grand_final)
		printf ("\n*** Last Line Reached [OR] Line not found ***\n");
	freedom_yolo((void **)&grand_final);
	return (0);
}

#endif

