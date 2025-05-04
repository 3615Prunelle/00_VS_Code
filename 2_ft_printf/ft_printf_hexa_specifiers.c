/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa_specifiers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:25:57 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/29 19:00:37 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	x_specifier(unsigned long long i, char *hexa);

int	p_specifier(void *p)
{
	uintptr_t	pos_ptr;
	int			count;

	if (!p)
		return (write (1, "(nil)", 5));
	pos_ptr = (uintptr_t) p;
	write (1, "0x", 2);
	count = x_specifier((unsigned long)pos_ptr, "0123456789abcdef");
	return (count + 2);
}

int	x_specifier(unsigned long long i, char *hexa)
{
	static int			count;
	char				c;

	count = 0;
	if (i / 16)
		x_specifier (i / 16, hexa);
	c = hexa [i % 16];
	write (1, &c, 1);
	count++;
	return (count);
}
