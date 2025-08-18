/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:46:04 by sophie            #+#    #+#             */
/*   Updated: 2025/08/11 18:13:50 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// ‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️ NEXT : Voir page Notion Minitalk ‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️
// ‼️‼️‼️‼️‼️‼️‼️‼️‼️‼️ Branche Client à merge quand débug fini

void	send_signal(int signum)
{
	// A importer depuis main
}

// Client sends a signal to server
int	main(int argc, char **argv)
{
	int		server_PID;
	char	*string_to_send;
	unsigned char *bin_array;

	if(argc == 3)
	{
		server_PID = ft_atoi(argv[1]);
		string_to_send = ft_strdup(argv[2]);			// Ⓜ️
		ft_printf("About to send message [%s] to server (PID [%i])\n", string_to_send, server_PID);
		ft_printf("Client PID : %i\n", getpid());	// Change à chaque fois

		bin_array = string_to_bit(string_to_send);		// Ⓜ️ Convertit toute la string et ajoute \n, pas juste char par char
		//ft_printf("Bin array : [%s]\n", (char *)bin_array);

		int i = 0;
		int j = 0;
		while (bin_array[i] != '\0')	// Va printer théoriquement le \n
		{
			j = 0;
			while(j < 8)
			{
				if(bin_array[i] == '0')
				{
					kill(server_PID, SIGUSR1);
					usleep(3000);
				}
				else if(bin_array[i] == '1')
				{
					kill(server_PID, SIGUSR2);
					usleep(3000);
				}
				else if(bin_array[i] == '\n')
				{
					send_newline_binary(server_PID);
					i++;
					break;	// Pour sortir juste de cette boucle, s'il y a des char à print après le \n
				}
				i++;
				j++;
			}
		}
		if (bin_array[i] == '\0')
		{
			exit(0);
		}
		// add a clean up function
	}
	return(0);
}
