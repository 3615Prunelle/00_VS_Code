#include "minitalk_server.h"

// volatile unsigned char buffer[7]; // les 6 premiers chars = size_t max est 5 char + \0 --- buffer[7] est un flag
unsigned char *buffer = NULL;

int		main(void)
{
	buffer = ft_calloc(sizeof(unsigned char), 7);
// Get process ID so I can reach out to it via terminal & kill command (kill -signo pid)
	int	process_id;
	process_id = getpid();
	ft_printf("Waiting for message from client - PID server is [%i]\n", process_id);

	struct sigaction	deal_with_signal;
	deal_with_signal.sa_sigaction = got_signal1;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&deal_with_signal.sa_mask);
	sigaddset(&deal_with_signal.sa_mask, SIGUSR1);
	sigaddset(&deal_with_signal.sa_mask, SIGUSR2);

	deal_with_signal.sa_flags = SA_SIGINFO;				// Pour récupérer le PID du client (entre autres)

	sigaction(SIGUSR1, &deal_with_signal, NULL);
	sigaction(SIGUSR2, &deal_with_signal, NULL);

	while (1)
	{
		while (ft_strlen((const char*)buffer) < 5) // sortir quand on a la taille du buffer
		{
			pause(); // marche aussi sans ? Check & remove if function too long
		}
		// ft_printf("VICTOIRE - Buffer for string size : %s\n", buffer);
		size_t size_of_string = ft_atoi((char*)buffer);
		// ft_printf("Size of buffer in int ? %d\n", size_of_string);
		// ft_printf("\t\t_________________ GOT SIZE _________________\n");
		free((void*)buffer);
		buffer = ft_calloc(sizeof(unsigned char), size_of_string + 1);			// \0 -- \n pas nécessaire car on le print à part
		while (ft_strlen((const char*)buffer) + 1 <= size_of_string)
		{
			// printf("\t\t\tBUFFER : %s\n", buffer);
			// printf("... Return Strlen %ld\n", ft_strlen((const char*)buffer));
			pause();
		}
		// printf("........ BUFFER : %s\n", buffer);
		int i = 0;
		// write(1, ".\n", 2);
		while (buffer[i] != '\0')
		{
			write(1, &buffer[i], 1);
			i++;
		}
		write(1, "\n", 1);
		free((void*)buffer);
		buffer = ft_calloc(sizeof(unsigned char), 7);	// reset pour prochain passage dans la boucle
	}


// add a clean up function ?
	return(0);
}
