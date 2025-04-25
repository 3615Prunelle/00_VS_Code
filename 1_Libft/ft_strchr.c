/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:33 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/19 19:07:38 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' || s[i] == (char)c)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *string = "Ptr to 1st occurrence of char c in str s";
// 	int c = 'i';

// 	char *xx = ft_strchr(string,c);
// 	char *tt = strchr(string, c);

// 	printf("My Ft:	%s\n", xx);
// 	printf("Strchr:	%s\n", tt);

// 	return (0);
// }
