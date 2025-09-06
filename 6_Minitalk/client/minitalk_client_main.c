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

bool ready_to_send = true;

void	send_string_size(unsigned char *converted_size_to_send, int server_PID)
{
	unsigned char	*size_binary_char_to_send;	// faire avec array plutôt que malloc ? car no need à l'extérieur de la fonction
	int	i = 0;

	static int sending_spaces;
	int	length_of_size_array = ft_strlen((char*)converted_size_to_send);

	while(i < length_of_size_array)
	{
		size_binary_char_to_send = malloc(sizeof(unsigned char) * 8);
		size_binary_char_to_send = char_to_binary(converted_size_to_send[i]);
		if (ready_to_send == true)
		{
			send_binary_char(size_binary_char_to_send, server_PID);	// if ready, send, then turn false
			// set on false
		}

		free(size_binary_char_to_send);
		// ft_printf("Sent digit (in ASCII form) : [%c]\n", converted_size_to_send[i]);
		i++;
	}
	if(converted_size_to_send[i] == '\0')
	{
		size_binary_char_to_send = malloc(sizeof(unsigned char) * 8);
		size_binary_char_to_send = char_to_binary(' ');
		if (ready_to_send == true)
		{
			send_binary_char(size_binary_char_to_send, server_PID);	// if ready, send, then turn false
			// set on false
		}
		free(size_binary_char_to_send);
		sending_spaces = 1;
		// ft_printf("----- Done sending 'digits' + one space ! About to send other spaces then the string.\n");
		i++;
	}
	while((i < 5) && (sending_spaces == 1))
	{
		size_binary_char_to_send = malloc(sizeof(unsigned char) * 8);
		size_binary_char_to_send = char_to_binary(' ');
		if (ready_to_send == true)
		{
			send_binary_char(size_binary_char_to_send, server_PID);	// if ready, send, then turn false
			// set on false
		}
		free(size_binary_char_to_send);
		// ft_printf("----- Sent space\n");
		i++;
	}
	// ft_printf("----- Done with arrays of zeros, now sending the string\n");
}

void	send_string(unsigned char *converted_string_to_send, int server_PID)
{
	unsigned char	*string_binary_char_to_send;	// faire avec array plutôt que malloc ? car no need à l'extérieur de la fonction
	int	i = 0;

	while(converted_string_to_send[i] != '\0')
	{
		string_binary_char_to_send = malloc(sizeof(unsigned char) * 8);
		string_binary_char_to_send = char_to_binary(converted_string_to_send[i]);
		if (ready_to_send == true)
		{
			send_binary_char(string_binary_char_to_send, server_PID);
			// set on false
		}

		free(string_binary_char_to_send);
		// ft_printf("Sent char : [%c]\n", converted_string_to_send[i]);
		i++;
	}
	if(converted_string_to_send[i] == '\0')
	{
		string_binary_char_to_send = malloc(sizeof(unsigned char) * 8);
		string_binary_char_to_send = char_to_binary('\0');
		if (ready_to_send == true)
		{
			send_binary_char(string_binary_char_to_send, server_PID);
			// set on false
		}
		free(string_binary_char_to_send);

		// string_binary_char_to_send = malloc(sizeof(unsigned char) * 8);		// No need ? Car on write un \n in server side
		// string_binary_char_to_send = char_to_binary('\n');
		// send_binary_char(string_binary_char_to_send, server_PID);
		// free(string_binary_char_to_send);
		// ft_printf("----- Done sending chars ! About to exit.\n");
	}
	exit(0);
}

void	send_binary_char(unsigned char *binary_char, int server_PID)
{
	int i = 0;
	while (i < 8)
	{
		if(binary_char[i] == '0')
		// if((binary_char[i] == '0') && ready_to_send == true)
		{
			kill(server_PID, SIGUSR1);
			// Use pause instead, to wait for signal from server ? + set that up on server side
			usleep(3000);		// remove when AR set up ? - Or create another one without sleep (bc sleep required before sending signal)
			// ready_to_send = false;
		}
		else
		// else if((binary_char[i] == '1') && ready_to_send == true)
		{
			kill(server_PID, SIGUSR2);
			// Use pause instead, to wait for signal from server ? + set that up on server side
			usleep(3000);		// remove when AR set up ?
			// ready_to_send = false;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				server_PID;
	int				string_length;
	unsigned char	*string_to_send;
	unsigned char	*converted_size_to_send;

	struct sigaction	received_signal_from_server;
	received_signal_from_server.sa_handler = print_reception;
	received_signal_from_server.sa_flags = 0;		// pas nécessaire mais avec cette config je ne peux pas mettre zéro (TBC)
	sigemptyset(&received_signal_from_server.sa_mask);
	sigaddset(&received_signal_from_server.sa_mask, SIGUSR1);
	sigaddset(&received_signal_from_server.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &received_signal_from_server, NULL);

	if(argc == 3)
	{
		server_PID = ft_atoi(argv[1]);
		string_to_send = (unsigned char*)ft_strdup(argv[2]);		// Ⓜ️
		ft_printf("About to send a message to server (PID [%i])\n", server_PID);
		ft_printf("Client PID : %i\n", getpid());	// Client PID change à chaque fois

		string_length = ft_strlen((char*)string_to_send);
		converted_size_to_send = (unsigned char*)ft_itoa(string_length);
		send_string_size(converted_size_to_send, server_PID);
		send_string(string_to_send, server_PID);
		exit(0);
	}
	return(0);
}

// void	print_reception(int signo, siginfo_t *info, void *other)	// Handler
void	print_reception(int signo)	// Handler
{
	if (signo == 10)
	{
		write(1, "\n\t\t** Signal 10 Received By Server **\n", 38);
	}

	if(signo == 12)
	{
		write(1, "\n\t\t** Signal 12 Received By Server **\n", 38);
		// ready_to_send = true;
	}
}
