/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:21:43 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/08 20:25:17 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	printf("%d\n", BUFFER_SIZE);

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (free_null_three(&buffer, NULL, NULL));
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer || read(fd, buffer, BUFFER_SIZE) <= 0)
			return (free_null_three(&buffer, NULL, NULL));
	}
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp)
		return (free_null_three(&buffer, NULL, NULL));
	line = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line)
		return (free_null_three(&buffer, NULL, &temp));
	read_line(fd, &buffer, &line, &temp);
	if (!line)
		return (free_null_three(&buffer, NULL, &temp));
	free(temp);
	return (line);
}

void	read_line(int fd, char **buffer, char **line, char **temp)
{
	int	len;

	while (*buffer)
	{
		if (ft_strchr(*buffer, '\n'))
		{
			len = (ft_strchr(*buffer, '\n') - *buffer);
			*temp = ft_strlcpy(*temp, *buffer, len + 1);
			len = ft_strlen(*buffer) - len;
			*buffer = ft_strlcpy(*buffer, ft_strchr(*buffer, '\n'), len + 1);
			*line = ft_strjoin_bis(*line, *temp);
			return ;
		}
		*line = ft_strjoin_bis(*line, *buffer);
		if (!*line)
			return ;
		ft_memset(*buffer, 0, BUFFER_SIZE);
		if (read(fd, *buffer, BUFFER_SIZE) <= 0)
		{
			if (*line && *line[0] == '\0')
				free_null_three(buffer, line, temp);
			return ;
		}
	}
}

char	*free_null_three(char **buff, char **line, char **temp)
{
	if (buff && *buff)
	{
		free(*buff);
		*buff = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (temp && *temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (NULL);
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
