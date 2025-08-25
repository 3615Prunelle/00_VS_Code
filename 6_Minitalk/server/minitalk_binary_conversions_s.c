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

#include "minitalk_server.h"

/*
Attendre d'avoir reçu la string pour la print
Recevoir, dans l'ordre :
	Size du PID (size_t)
	PID
	Size string (size_t)
	String
*/

// int		build_client_PID(unsigned char *one_char)
// {
// 	int i = 0;

// }

// A changer (ne doit pas print one by one)
void 	print_char_from_binary(unsigned char *binary_array)
{
	int i = 0;
	int number_to_conv = 0;
	int bin_compare = 128;
	char c;

	while (i < 8)				// car binary_array n'a que 8 éléments
	{
		if (binary_array[i] == '1')
		{
			number_to_conv += bin_compare;
		}
		bin_compare /= 2;
		i++;
	}
	c = number_to_conv;
	write(1, &c, 1);			// VICTOIRE
}
int		get_int_from_binary(unsigned char *binary_array)
{
	int i = 0;
	int number = 0;
	int bin_compare = 128;
	char c;

	while (i < 8)				// car binary_array n'a que 8 éléments
	{
		if (binary_array[i] == 1)
		{
			number += bin_compare;
		}
		bin_compare /= 2;
		i++;
	}
	return(number);
}
