/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:24 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:50 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while ((i < len) && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && i + j < len)
		{
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *) big + i);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char big[] = "Pointer to lil text in big in a size_t limit";
// 	char lil[] = "big";

// 	char *oo = ft_strnstr(big, lil, 15);
// 	char *zz = strnstr(big, lil, 15);

// 	printf("My Ft:		%s\n", oo);
// 	printf("Strnstr:	%s\n", zz);

// 	return (0);
// }
