/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_binary_conversions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:46:04 by sophie            #+#    #+#             */
/*   Updated: 2025/08/11 18:13:50 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

unsigned char	*char_to_binary(unsigned char c)
{
	int bitmask = 128;		// N'évolue pas car on vérifie toujours le premier bit (et on shift le binaire du char vers la gauche)
	int i = 0;
	unsigned char	*converted_char;
	converted_char = malloc(sizeof(unsigned char) * 8);		// un seul char

	while(i < 8)
	{
		if(c & bitmask)
		{
			converted_char[i] = '1';
		}
		else
		{
			converted_char[i] = '0';
		}
		i++;
		c = c << 1;
	}
	return(converted_char);
}
