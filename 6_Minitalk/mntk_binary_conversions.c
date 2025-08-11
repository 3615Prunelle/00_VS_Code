/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mntk_binary_conversions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:46:04 by sophie            #+#    #+#             */
/*   Updated: 2025/08/11 15:18:14 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		*string_to_bit(char *s)
{
	unsigned char	*bin_array;
	// unsigned char = 1 byte/octet = 8 bits
	// toujours utiliser unsigned char si pas besoin de neg (good practice)

	return(bin_array);
}
char	*bit_to_string(unsigned char *bin_array)
{
	// TO DO
}
int		main(void)
{
	char	s[] = "Hello";
	unsigned char conv_to_bin = string_to_bit(s);

	printf("Binary from Hello is : [%s]\n", conv_to_bin);

	return(0);
}
