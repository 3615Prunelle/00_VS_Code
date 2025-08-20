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

// ‼️‼️ Utiliser branche client pour debug ‼️‼️

void	send_signal(int signum)
{
	// A importer depuis main si elle fait plus de 25 lignes
}

// Client sends a signal to server
int	main(int argc, char **argv)
{
	int		server_PID;
	char	*string_to_send;
	int		i;
	char	*client_PID;

	i = 0;
	if(argc == 3)
	{
		server_PID = ft_atoi(argv[1]);
		string_to_send = ft_strdup(argv[2]);		// Ⓜ️
		ft_printf("About to send a message to server (PID [%i])\n", server_PID);
		ft_printf("Client PID : %i\n", getpid());	// Client PID change à chaque fois

		// envoyer le PID du client par signaux, avant ou après la string (maybe better before ?)
		client_PID = ft_itoa(getpid());
		while(client_PID[i] != '\0')
		{
			char_to_binary(client_PID[i], server_PID);
			i++;
		}

		// i = 0;
		// while(string_to_send[i] != '\0')
		// {
		// 	char_to_binary(string_to_send[i], server_PID);
		// 	i++;
		// }
		// if(string_to_send[i] == '\0')
		// {
		// 	char_to_binary('\n', server_PID);
		// 	exit(0);
		// }
	}
	return(0);
}
