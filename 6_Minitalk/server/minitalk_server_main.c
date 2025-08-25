/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

// ‼️Use other branch to debug

#include "minitalk_server.h"

int		main(void)
{
// Get process ID so I can reach out to it via terminal & kill command (kill -signum pid)
	int	process_id;
	process_id = getpid();
	ft_printf("Waiting for message from client - PID server is [%i]\n", process_id);

	struct sigaction	print_string;
	// struct sigaction	send_signal;	// A faire

	print_string.sa_handler = got_signal;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&print_string.sa_mask);
	sigaddset(&print_string.sa_mask, SIGUSR1);
	sigaddset(&print_string.sa_mask, SIGUSR2);

	print_string.sa_flags = 0;				// A faire sinon bugs

	// int sigaction_return1;
	// int sigaction_return2;
	// sigaction_return1 = sigaction(SIGUSR1, &print_string, NULL);
	// sigaction_return2 = sigaction(SIGUSR2, &print_string, NULL);

	sigaction(SIGUSR1, &print_string, NULL);
	sigaction(SIGUSR2, &print_string, NULL);

	// if((sigaction_return1 == -1) || (sigaction_return2 == -1))		// Pour débug ?
	// {
	// 	ft_printf("Sigaction return 1 : [%i]\n", sigaction_return1);
	// 	ft_printf("Sigaction return 2 : [%i]\n", sigaction_return2);
	// 	ft_printf("Errno message : [%s]\n", strerror(errno));
	// }

// récupérer size puis PID du client (avant de print chaque string)
// première boucle while pour le PID size
// envoyer signal au client
// print string

	while (1)		// if no loop, exit after the first signal received
	{
		pause(); // marche aussi si je ne le mets pas, à retirer si need to remove 3 lines

		// créer une fonction par action : get_client_PID // send_signal_to_client // receive&print_string
		// chacune avec leur struct et une boucle while ?
	}

// add a clean up function ?
	return(0);
}
