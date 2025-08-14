/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

#include "minitalk.h"

// faire.h séparé avec string to bin/bit et reverse et les tester en dehors du project

void	got_signal(int signum)
{
	//  typedef typeof(void (int))  *sighandler_t;
	// sighandler_t; est une fonction qui renvoie void et prend un int en param
	// ft_printf("Got here - Signal : %i\n", signum);

	static int				bit_count;
	static unsigned char	*one_char;					// = 1 bit
	if (bit_count == 0)
	{
		one_char = malloc(sizeof(unsigned char) * 8);	// ajouter if malloc fails + free
	}
	if (bit_count == 8)
	{
		bit_count = 0;
		free(one_char);
		one_char = malloc(sizeof(unsigned char) * 8);	// ajouter if malloc fails + free
	}
	if (bit_count < 8)
	{
		if (signum == 10)
		{
			one_char[bit_count] = '0';
		}
		if (signum == 12)
		{
			one_char[bit_count] = '1';
		}
		bit_count++;
	}
	if (bit_count == 8)	// tous les 8 signaux, appel de fonction qui va convertir 8 bits en char, et les print
	{
		if(ft_strncmp((char*)one_char, "11111111", 8) == 0)
		{
			usleep(1000);
			write(1, "\n", 1);
			ft_printf("\t\tLa fin du hari-string\n");
		}
		else
		{
			print_char_from_8bits(one_char);
			// ft_printf("\t<<< Binary for that letter : [%s]\n", (char*)one_char);
		}
	}

	// if (!(signum))	// Useless, find another way to exit
	// {
	// 	ft_printf("About to exit\n");
	// 	exit(0);
	// }
}

// Server expects a signal from client
int		main(void)
{
// Get process ID so we can reach out to it via terminal & kill command (kill -signum pid)
	int	process_id;
	process_id = getpid();
	ft_printf("Waiting for message from client - PID server is [%i]\n", process_id);

	struct sigaction	action_to_launch;
	action_to_launch.__sigaction_handler;		// (2 options) Fonction à appeler (simple ou avancée)
	action_to_launch.sa_flags;					// int - Options qui changent le comportement (SA_SIGINFO → utiliser sa_sigaction au lieu de sa_handler. SA_RESTART → relancer les appels systèmes interrompus. Etc.)
	action_to_launch.sa_mask;					// sigset_t (array of bool) - Signaux à bloquer pendant que le handler tourne
	action_to_launch.sa_restorer;				// Vieux champ historique pour remettre un handler précédent. Ne pas utiliser.

	action_to_launch.sa_handler = got_signal;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&action_to_launch.sa_mask);
	sigaddset(&action_to_launch.sa_mask, SIGUSR1);
	sigaddset(&action_to_launch.sa_mask, SIGUSR2);

	action_to_launch.sa_flags = 0;				// A faire sinon exit après 3 kill commands - A investiguer

	int sigaction_return;
	sigaction_return = sigaction(SIGUSR1, &action_to_launch, NULL);		// A privilégier plutôt que signal (plus fiable)
	sigaction_return = sigaction(SIGUSR2, &action_to_launch, NULL);
// arg 1 : numéro du signal à gérer
// arg 2 : action quand le signal arrive - adresse d’une structure struct sigaction définie au dessus
// arg 3 : si on veut savoir quelle action était définie avant pour ce signal = pointeur vers une autre struct sigaction. Sinon, NULL
// return : 0 if success, -1 +errno if error
//	ft_printf("Sigaction return : [%i]\n", sigaction_return);
//	ft_printf("Errno message : [%s]\n", strerror(errno));				// Pas autorisée, use only for testing

	while (1)		// if no loop, exit after the first signal received
	{
		pause();	// attendre un signal (returns a int, what to do with it ?) - Useless ?
	}


	return(0);
}
