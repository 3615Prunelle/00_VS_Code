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

#include "minitalk_client.h"

// ‼️‼️ Utiliser branche client pour debug ‼️‼️

void	send_PID(char *client_PID, int server_PID)
{
		int i = 0;
		size_t	size_PID;
		size_PID = ft_strlen(client_PID);
		char *size_to_ascii = ft_itoa(size_PID);	// string : "5 \0"

		unsigned char *size_to_send = char_to_binary(size_to_ascii[0]);

		send_binary_char(size_to_send, server_PID);

		// // A faire quand server a bien recu la size
		// while(client_PID[i] != '\0')
		// {
		// 	// déclarer variable unsigned char pour mettre le return de char_to_binary, un chiffre après l'autre
		// 	// puis envoyer cette suite binaire au server
		// 	char_to_binary(client_PID[i]);
		// 	i++;
		// }
}

void	send_binary_char(unsigned char *binary_char, int server_PID)
{
	int i = 0;
	while (i < 8)
	{
		if(binary_char[i] == '0')
		{
			kill(server_PID, SIGUSR1);
			sleep(1);				// remove when AR set up
		}
		else
		{
			kill(server_PID, SIGUSR2);
			sleep(1);				// remove when AR set up
		}
		i++;
	}
}

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

		client_PID = ft_itoa(getpid());
		send_PID(client_PID, server_PID);


		// i = 0;
		// while(string_to_send[i] != '\0')
		// {
		// 	char_to_binary(string_to_send[i]);
		// 	i++;
		// }
		// if(string_to_send[i] == '\0')
		// {
		// 	char_to_binary('\n');
		// 	exit(0);
		// }
	}
	return(0);
}
