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

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!buffer)
	{
		buffer = ft_calloc (BUFFER_SIZE + 1, 1);
		read (fd, buffer, BUFFER_SIZE);
	}
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	line = ft_calloc(BUFFER_SIZE + 1, 1);
	read_line(fd, &buffer, &line, &temp);
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

//#define ROUQUINETTE_DEBUG //comment out uniquement cette ligne au de tout le reste en dessous
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
	const char	*path_to_file;
	int			file_descriptor;
	int			line_number;
	char		*grand_final;

	//path_to_file = "Invalid File Descriptor";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/empty";
	path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/41_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/41_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/42_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/42_with_nl"";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/43_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/43_with_nl"";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_nlx5";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/multiple_line_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/alternate_line_nl_with_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_no_nl";
	//path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/gnlTester/files/big_line_with_nl";

	file_descriptor = open (path_to_file, O_RDONLY);
	line_number = 1;
	grand_final = ft_calloc(1, 1);

	while (grand_final != (NULL))
	{
		freedom_yolo ((void **)&grand_final);
		grand_final = get_next_line(file_descriptor);
		if (grand_final == NULL)
			break ;
		printf ("[Line %i]	%s", line_number, grand_final);
		line_number++;
	}
	if (!grand_final)
		printf ("\n*** Last Line Reached [OR] Line not found ***\n");
	freedom_yolo((void **)&grand_final);
	return (0);
}

#endif

