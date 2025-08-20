/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

// ‼️‼️‼️Ne pas faire de modifs sur le fichier client dans VSCode principal

#include "minitalk.h"

void	receiving_PID(int signum)
{
	static int	bit_count;
	static bool	one_char[8];
	static int	client_pid[7];	// PID Max = 4194304 (cmd shell : cat /proc/sys/kernel/pid_max)

	if (bit_count == 8)
		bit_count = 0;
	if (bit_count < 8)
	{
		if (signum == 10)
			one_char[bit_count] = 0;
		else if (signum == 12)
			one_char[bit_count] = 1;
		bit_count++;
	}
	if (bit_count == 8)	// tous les 8 signaux, appel de fonction qui va mettre le char dans une string, puis la convertir en int
	{
			// Convertir one_char(binaire) en char
			// le mettre dans une string (problème : on ne connait pas la taille du PID)
			// faire un atoi pour convertir la string en int
			// envoyer un signal
	}
}
void	got_signal(int signum)
{
	// typedef typeof(void (int))  *sighandler_t;
	// sighandler_t; est une fonction qui renvoie void et prend un int en param

	static int	bit_count;
	static bool	one_char[8];

	if (bit_count == 8)
		bit_count = 0;
	if (bit_count < 8)
	{
		if (signum == 10)
			one_char[bit_count] = 0;
		else if (signum == 12)
			one_char[bit_count] = 1;
		bit_count++;
	}
	if (bit_count == 8)	// tous les 8 signaux, appel de fonction qui va convertir 8 bits en char, et les print
	{
			print_char_from_binary(one_char);
	}
// add a clean up function ?
}

int		main(void)
{
// Get process ID so we can reach out to it via terminal & kill command (kill -signum pid)
	int	process_id;
	process_id = getpid();
	ft_printf("Waiting for message from client - PID server is [%i]\n", process_id);

	struct sigaction	print_string;
	struct sigaction	send_signal;

	print_string.sa_handler = got_signal;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&print_string.sa_mask);
	sigaddset(&print_string.sa_mask, SIGUSR1);
	sigaddset(&print_string.sa_mask, SIGUSR2);

	print_string.sa_flags = 0;				// A faire sinon exit après 3 kill commands - A investiguer

	int sigaction_return1;
	int sigaction_return2;
	sigaction_return1 = sigaction(SIGUSR1, &print_string, NULL);		// A privilégier plutôt que signal (plus fiable)
	sigaction_return2 = sigaction(SIGUSR2, &print_string, NULL);

	// if((sigaction_return1 == -1) || (sigaction_return2 == -1))
	// {
	// 	ft_printf("Sigaction return 1 : [%i]\n", sigaction_return1);
	// 	ft_printf("Sigaction return 2 : [%i]\n", sigaction_return2);
	// 	ft_printf("Errno message : [%s]\n", strerror(errno));
	// }

// récupérer le PID du client (avant de print chaque string)
// première boucle while pour le PID (tant que le char est un chiffre ?)
// envoyer signal au client
// print string

	while (1)		// if no loop, exit after the first signal received
	{
		pause(); // marche aussi si je ne le mets pas, à retirer si need to remove 3 lines

		// sigaction_return1 = sigaction(SIGUSR1, &print_string, NULL);		// A privilégier plutôt que signal (plus fiable)
		// sigaction_return2 = sigaction(SIGUSR2, &print_string, NULL);

		// if((sigaction_return1 == -1) || (sigaction_return2 == -1))				// A tester uniquement pour débug (errno pas autorisé)
		// {
		// 	ft_printf("Sigaction return 1 : [%i]\n", sigaction_return1);
		// 	ft_printf("Sigaction return 2 : [%i]\n", sigaction_return2);
		// 	ft_printf("Errno message : [%s]\n", strerror(errno));
		// }
	}

// add a clean up function ?
	return(0);
}
