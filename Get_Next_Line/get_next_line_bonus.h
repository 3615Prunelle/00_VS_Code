/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/03/23 21:36:03 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Name of new library defined here (so we can use #include "current_ft.h")
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

//All #include only here (put #include "current_ft.h" is in each file)
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

//For test purposes only, comment out when done
# include <stdio.h>
# include <limits.h>

//All #define can be placed only here
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
# endif

// Main Function
char		*get_next_line(int fd);

// Helpers
void		read_line(int fd, char **buffer, char **line, char **temp);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *str, int constante, size_t taille);
size_t		ft_strlen(const char *str);
int			newline_index_check(char *buffer);
int			n_counter(char *buffer);
char		*ft_strchr(const char *s, int c);
char		*ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strjoin_bis(char *s1, char *s2);

#endif
