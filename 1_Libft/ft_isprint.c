/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:33 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 12:46:42 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
// 	unsigned char test = 127;

// 	printf("Mine:		%d\n", ft_isprint(test));
// 	printf("Official:	%d\n", isprint(test));
// 	return (0);
// }
