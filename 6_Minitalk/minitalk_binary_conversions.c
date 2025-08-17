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

// Si fonction trop longue, faire tech de Fab (voir page Minitalk Notion)
unsigned char	*string_to_bit(char *s)
{
	// unsigned char = 1 byte/octet = 8 bits
	// toujours utiliser unsigned char si pas besoin de nombres negatifs (good practice)
	unsigned char	*bin_array;

	int length_string = strlen(s);

	bin_array = malloc(sizeof(unsigned char) * (length_string+1) * 8);	// 8 car 8 bits par char - +1 car j'ajoute un \n à la fin

	int i = 0;	// pour s
	int j = 0;	// pour bin_array
	int conv = 0;
	int bin_compare = 128;

	while(s[i] != '\0')
	{
		conv = (int)s[i];	// convertir le char en int - cast surement pas nécessaire

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
	bin_array[j] = '\n';		// mettre un /n + 1 char en plus au lieu de 11111111

	return(bin_array);
}
void 	print_char_from_8bits(unsigned char *bin_array) // change to void return after tests
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

int	main(void)
{
	char *s = "Bonjour";
}
