/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

#include "mntk.h"

// faire.h séparé avec string to bin/bit et reverse et les tester en dehors du project

void	got_signal(int signum)
{
	//  typedef typeof(void (int))  *sighandler_t;
	// sighandler_t; est une fonction qui renvoie void et prend un int en param
	printf("Got here - Signal : %i\n", signum);

	// if signum = 10, put int 0 in a int array
	// if signum = 12, put int 1 in a int array
	// exit when no more signal received ?
}

int		main(void)
{
	// Server expect a signal from client
	int	process_id;
	process_id = getpid();
	printf("PID server is : %i\n", process_id);
	printf("Waiting for message from client\n");

	signal(SIGUSR1, got_signal);	// got_signal is a callback function
	signal(SIGUSR2, got_signal);

	while (1)
	{
		sleep(1);
	}


	pause();	// attendre un signal - returns a int, what to do with it ?
	printf("About to receive a signal from client - PID [%i]\n", process_id);


	printf("Error ? : [%s]", strerror(errno));

	return(0);
}
