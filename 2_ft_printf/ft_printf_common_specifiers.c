/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_common_specifiers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:25:57 by schappuy          #+#    #+#             */
/*   Updated: 2025/02/26 21:20:58 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int				s_specifier(char *c);
int				d_and_i_specifier(int i);
unsigned int	u_specifier(unsigned int i);

int	c_specifier(char c)
{
	write (1, &c, 1);
	return (1);
}

int	s_specifier(char *c)
{
	int	size;

	if (!c)
	{
		write(1, "(null)", 6);
		return (6);
	}
	size = ft_strlen(c);
	write (1, c, size);
	return (size);
}

int	d_and_i_specifier(int i)
{
	char	*itoa_conv;
	int		length_itoa;

	itoa_conv = ft_itoa(i);
	length_itoa = ft_strlen(itoa_conv);
	write (1, itoa_conv, length_itoa);
	free(itoa_conv);
	return (length_itoa);
}

unsigned int	u_specifier(unsigned int i)
{
	char		c;
	static int	count;

	count = 0;
	if (i / 10)
		u_specifier(i / 10);
	c = (i % 10) + '0';
	write(1, &c, 1);
	count++;
	return (count);
}
