/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

// ‼️Use other branch to debug

#include "minitalk_server.h"

void	get_client_PID(void)		// Action 1
{
	// receive size first (1 char)
	// malloc (outside of handler) or declare array of unsigned char [size]
	// receive PID and fill up array
	// send signal to client
	struct sigaction	client_PID_related_actions;		// A faire
	client_PID_related_actions.sa_handler = receive_PID;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&client_PID_related_actions.sa_mask);
	sigaddset(&client_PID_related_actions.sa_mask, SIGUSR1);
	sigaddset(&client_PID_related_actions.sa_mask, SIGUSR2);

	client_PID_related_actions.sa_flags = 0;				// A faire sinon buggy

	int sigaction_return1;		// pour back up le return (-1 si erreur)
	int sigaction_return2;
	sigaction_return1 = sigaction(SIGUSR1, &client_PID_related_actions, NULL);
	sigaction_return2 = sigaction(SIGUSR2, &client_PID_related_actions, NULL);

	while(1)
	{
		pause();
	}
}

// void		handler(int signo, siginfo_t *info, void *other)
void	receive_PID(int signum)		// Handler - Change signature to (see above)
{
	// PID Max = 4194304 (cmd shell : cat /proc/sys/kernel/pid_max) = 7 chars
	static int				bit_count;
	static unsigned char	one_char[8];
	static int				got_size = 0;
	static int 				length_of_client_PID;
	static int				i;

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
	if (bit_count == 8)	// tous les 8 signaux, appel de fonction
	{
		// le premier char sera la size, puis on recevra le PID
		if(got_size == 0)		// Pour ne passer qu'une seule fois ici
		{
			length_of_client_PID = get_int_from_binary(one_char);
			got_size = 1;
		}
		else
		{
			unsigned char client_PID[length_of_client_PID];
			while (i < length_of_client_PID)
			{
				client_PID[i] = get_int_from_binary(one_char);
				i++;
			}
		}
	}
}

// void		handler(int signo, siginfo_t *info, void *other)
void	got_signal(int signum)
{
	// typedef typeof(void (int))  *sighandler_t;
	// sighandler_t; est une fonction qui renvoie void et prend un int en param

	static int	bit_count;
	static unsigned char	one_char[8];

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

