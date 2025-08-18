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

bool	*char_to_binary(char c)
{
	bool *bool_array;
	int bitmask = 1;		// N'évolue pas car on vérifie toujours le dernier bit (et on shift le binaire du char vers la droite)
	bool_array = malloc (sizeof(bool) * 8);		// un bool = 1 bit, donc on ne peut pas mettre de \n dedans - Maybe pas besoin car \n a une valeur binaire
	int i = 0;

	// ft_printf("Char is %c - Its ASCII is %d\n", c, c);

	while(i < 8)
	{
		if(c & bitmask)
			bool_array[7-i] = 1;
		else
			bool_array[7-i] = 0;
		i++;
		c = c >> 1;
	}
	return(bool_array);
}

// Si fonction trop longue, faire tech de Fab (voir page Minitalk Notion)
unsigned char	*string_to_bit(char *s)
{
	// unsigned char = 1 byte/octet = 8 bits
	// toujours utiliser unsigned char si pas besoin de nombres negatifs (good practice)
	unsigned char	*bin_array;

	int length_string = strlen(s);

	bin_array = ft_calloc(sizeof(unsigned char), (length_string+1) * 8);	// 8 car 8 bits par char - +1 car j'ajoute un \n à la fin

	int i = 0;	// pour s
	int j = 0;	// pour bin_array
	int conv = 0;
	int bin_compare = 128;

	while(s[i] != '\0')
	{
		conv = s[i];	// convertir le char en int

		// convertir le int en binaire et stocker dans une string de unsigned chars
		bin_compare = 128;
		while (bin_compare != 0)
		{
			if(conv >= bin_compare)
			{
				bin_array[j] = '1';
				conv = conv - bin_compare;
			}
			else
			{
				bin_array[j] = '0';
			}
			j++;
			bin_compare /= 2;
		}
		i++;
	}
	bin_array[j] = '\n';		// Condition d'arrêt / exit du client + retour à la ligne du server - Mais n'est pas converti en binaire
	bin_array[j+1] = '\0';
	return(bin_array);
}
void 	print_char_from_8bits(unsigned char *bin_array)
{
	int i = 0;
	int j = 0;
	int k;
	int number_to_conv;
	int bin_compare;
	char c;

	while (bin_array[j] != '\0')
	{
		number_to_conv = 0;
		bin_compare = 128;
		k = 8;
		while(k > 0)	// prendre les 8 premiers chars - pas nécessaire ici car on en recoit toujours 8 ?
		{
			if (bin_array[j] == '1')
			{
				number_to_conv += bin_compare;
			}
			j++;
			k--;
			bin_compare /= 2;
		}
		c = number_to_conv;
		write(1, &c, 1);			// VICTOIRE
		i++;
	}
}

void	send_newline_binary(int server_PID)
{
	// Bin for \n is 0000 10 10
	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);

	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);

	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);

	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);

	kill(server_PID, SIGUSR2);		// 1
	usleep(3000);

	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);

	kill(server_PID, SIGUSR2);		// 1
	usleep(3000);

	kill(server_PID, SIGUSR1);		// 0
	usleep(3000);
}
