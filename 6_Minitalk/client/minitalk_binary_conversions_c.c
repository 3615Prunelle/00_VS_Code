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

/*
Envoyer, dans l'ordre :
	Size du PID (size_t)
	PID
	Size string (size_t)
	String
*/


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
