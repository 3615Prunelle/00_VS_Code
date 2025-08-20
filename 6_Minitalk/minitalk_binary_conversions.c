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

int		build_client_PID(bool *one_char)
{
	int i = 0;
	int number_in_ASCII_format = 0;
	int bin_compare = 128;
	char c;

	while (i < 8)				// car binary_array n'a que 8 éléments
	{
		if (one_char[i] == 1)
		{
			number_in_ASCII_format += bin_compare;
		}
		bin_compare /= 2;
		i++;
	}
	c = number_in_ASCII_format;	// on a le premier chiffre, mais on veut récupérer le dernier


// ‼️‼️‼️ Apprendre à gérer la récursivité then come back here ‼️‼️‼️
// Ou pas : envoyer la taille du PID puis PID puis string
// envoyer aussi la taille de la string (size_t) car ma tech n'est pas authorisée (recevoir PUIS print)
// envoyer la taille du PID


	int	client_PID;
	static char *int_string;

	// faire récursive pour commencer par la fin >> Not anymore

	if(one_char)



	return(client_PID);
}

void	char_to_binary(char c, int server_PID)
{
	int bitmask = 128;		// N'évolue pas car on vérifie toujours le premier bit (et on shift le binaire du char vers la gauche)
	int i = 0;

	while(i < 8)
	{
		if(c & bitmask)
		{
			kill(server_PID, SIGUSR2);
			usleep(600);
		}
		else
		{
			kill(server_PID, SIGUSR1);
			usleep(600);
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

	while (i < 8)				// car binary_array n'a que 8 éléments
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
