/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/02/26 19:06:47 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static size_t	get_size(int n);

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	size_t	size;

	num = n;
	size = get_size(n);
	if (n < 0)
		num = -num;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size--] = '\0';
	while (num > 0)
	{
		str[size--] = num % 10 + '0';
		num /= 10;
	}
	if (size == 0 && str[1] == '\0')
		str[size] = '0';
	else if (size == 0 && str[1])
		str[size] = '-';
	return (str);
}

static size_t	get_size(int n)
{
	size_t	size;

	if (n > 0)
		size = 0;
	else
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

// #include <stdio.h>

// int main(void)
// {
//     int p = -123;
//     int q = 123;
//     int r = p * q;
//     int s = 0;
//     int t = 8;

//     char *ppp = ft_itoa(p);
//     char *qqq = ft_itoa(q);
//     char *rrr = ft_itoa(r);
//     char *sss = ft_itoa(s);
//     char *ttt = ft_itoa(t);

//     printf("%i =	%s\n", p, ppp);
//     printf("%i =	%s\n", q, qqq);
//     printf("%i =	%s\n", r, rrr);
//     printf("%i =	%s\n", s, sss);
//     printf("%i =	%s\n", t, ttt);

//     free(ppp);
//     free(qqq);
//     free(rrr);
//     free(sss);
//     free(ttt);

//     return (0);
// }
