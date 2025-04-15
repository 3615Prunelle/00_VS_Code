/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 12:25:16 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// void	ft_toupper3(unsigned int index, char *str)
// {
// 	char maj = ft_toupper(str[index]);
// 	str[index] = maj;
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char before[] = "Each char will be changed in memory";

// 	ft_striteri(before, ft_toupper3);

// 	printf("%s", before);

// 	return (0);
// }
