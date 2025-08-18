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

#include "minitalk.h"

void	char_to_binary(char c, int server_PID)
{
	bool *bool_array;
	int bitmask = 128;		// N'évolue pas car on vérifie toujours le premier bit (et on shift le binaire du char vers la gauche)
	bool_array = malloc (sizeof(bool) * 8);		// bool = 1 byte = on peut mettre le binaire de \n dedans
	int i = 0;

	// ft_printf("Char is %c - Its ASCII is %d\n", c, c);

	while(i < 8)
	{
		if(c & bitmask)
		{
			bool_array[i] = 1;
			kill(server_PID, SIGUSR2);
			usleep(3000);				// Test avec pauses plus courtes
		}
		else
		{
			bool_array[i] = 0;
			kill(server_PID, SIGUSR1);
			usleep(3000);				// Test avec pauses plus courtes
		}
		i++;
		c = c << 1;
	}
}

void 	print_char_from_binary(bool *binary_array)
{
	int i = 0;
	int number_to_conv = 0;
	int bin_compare = 128;
	char c;

	while (i < 8)	// car binary_array n'a que 8 éléments
	{
		if (binary_array[i] == 1)
		{
			number_to_conv += bin_compare;
		}
		bin_compare /= 2;
		i++;
	}
	c = number_to_conv;
	write(1, &c, 1);			// VICTOIRE
}
