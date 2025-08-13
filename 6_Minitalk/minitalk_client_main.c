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

int	main(int argc, char **argv)
{
	// Send a signal to server
	// Do it only when server is set up, so I can test & debug
	// Open 2 VScode simultaneously to debug both processes
	int		server_PID;
	char	*string_to_send;

	if(argc == 3)
	{
		server_PID = ft_atoi(argv[1]);
		string_to_send = ft_strdup(argv[2]);
		ft_printf("About to send message [%s] to server (PID [%i])\n", string_to_send, server_PID);

		// appel de fonction (TO DO) qui va transformer la string en binaire (et la renvoyer)

		// set up signaux SIGUSR1 et SIGUSR2 (1 et 0)
		// USR1 = 10	USR2 = 12

		// créer une boucle pour envoyer les signaux un par un avec la fonction kill
	}


	return(0);
}
