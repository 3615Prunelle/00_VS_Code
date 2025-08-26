/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

#include "minitalk_server.h"

volatile unsigned char buffer[6]; // car size_t max est 5 char + \0

int		main(void)
{
// Get process ID so I can reach out to it via terminal & kill command (kill -signo pid)
	int	process_id;
	process_id = getpid();
	ft_printf("Waiting for message from client - PID server is [%i]\n", process_id);

	struct sigaction	deal_with_signal;
	deal_with_signal.sa_sigaction = got_signal;

// actions on 'set' : set it to empty, then add the 2 only authorized signals in it
	sigemptyset(&deal_with_signal.sa_mask);
	sigaddset(&deal_with_signal.sa_mask, SIGUSR1);
	sigaddset(&deal_with_signal.sa_mask, SIGUSR2);

	deal_with_signal.sa_flags = SA_SIGINFO;				// Pour récupérer le PID du client (entre autres)

	sigaction(SIGUSR1, &deal_with_signal, NULL);
	sigaction(SIGUSR2, &deal_with_signal, NULL);

	// int sigaction_return1;					// Pour débug ?
	// int sigaction_return2;
	// sigaction_return1 = sigaction(SIGUSR1, &deal_with_signal, NULL);
	// sigaction_return2 = sigaction(SIGUSR2, &deal_with_signal, NULL);
	// if((sigaction_return1 == -1) || (sigaction_return2 == -1))
	// {
	// 	ft_printf("Sigaction return 1 : [%i]\n", sigaction_return1);
	// 	ft_printf("Sigaction return 2 : [%i]\n", sigaction_return2);
	// 	ft_printf("Errno message : [%s]\n", strerror(errno));
	// }

	// while (volatile_number == 0)

	while (ft_strlen((const char*)buffer) < 5) // puis sortir, puis malloc, puis boucle while pour remplir buffer?
	{
		pause(); // marche aussi sans ? Check & retirer si need to remove 3 lines
	}

	ft_printf("VICTOIRE - Buffer : %s\n", buffer);
	size_t size_of_string = ft_atoi((char*)buffer);
	ft_printf("Size of buffer in int ? %d\n", size_of_string);

	unsigned char	*da_string;
	da_string = malloc(sizeof(unsigned char) * size_of_string);

	while (1)
	{
		ft_printf("Début Boucle while - Buffer : %s\n", buffer);
		// recevoir les char
		// les mettre 5 par 5 dans le buffer
		// vider le buffer dans la string à la suite - HOW ? ft_strjoin ?
		pause();
		ft_printf("Fin Boucle while - Buffer : %s\n", buffer);
	}


// add a clean up function ?
	return(0);
}

void	got_signal(int signo, siginfo_t *info, void *other)	// Handler (can't change signature)
{
	(void)other;	// sinon -Werror me met une erreur (unused param)

	static int				bit_count;
	static unsigned char	one_char_binary_array[8];
	int						client_PID;
	static int				first_pass;
	static int				total_count;
// write(1, "\n\t\t\t\t\t\t******PASS******\n", 24);
	if(first_pass == 0)
	{
		client_PID = info->si_pid;
		write(1, "Sending first signal to client\n", 31);
		kill(client_PID, SIGUSR1);
		first_pass = 1;
	}
	if (bit_count == 8)
	{
		bit_count = 0;
		ft_memset(one_char_binary_array, 0, 8);	// nécessaire ?
	}
	if (bit_count < 8)
	{
		if (signo == 10)
		{
			one_char_binary_array[bit_count] = '0';
			// write(1, "\t\t\t\t\t\t0\n", 8);
			kill(client_PID, SIGUSR1);
		}
		else if (signo == 12)
		{
			one_char_binary_array[bit_count] = '1';
			// write(1, "\t\t\t\t\t\t1\n", 8);
			kill(client_PID, SIGUSR1);
		}
		bit_count++;
		total_count++;
	}
	if ((bit_count == 8) && (total_count < 45))
	{
		ft_printf("\n--------------- Char just received (to encrypt) : [%c]\n", get_char_from_binary(one_char_binary_array));
		get_size_string(one_char_binary_array);
	}
	// else if ((bit_count == 8) && (total_count >= 45))			// 8 (bits) * 5 (size of buffer without \0)
	// {
	// 	get_string(one_char_binary_array);
	// }
}

void	get_string(unsigned char *one_char_binary_array)
{
	static int i;
	if((ft_strncmp((char*)one_char_binary_array, "00000000", 8) != 0) && (i < 5))		// null terminator = fin de la string
	{
		printf("(string) one_char_binary_array : [%s]\n", one_char_binary_array);
		buffer[i] = get_char_from_binary(one_char_binary_array);
		printf("\t\t\t\t\t\tNew buffer char >> [%c]\n", buffer[i]);
		i++;
	}
	else if(ft_strncmp((char*)one_char_binary_array, "00000000", 8) == 0)		// 5 = buffer size sans le \0
	{
		printf("(string) one_char_binary_array : [%s]\n", one_char_binary_array);
		buffer[i] = '\n';
		printf("\t\t\tEnd of the party - Line break (theorically)");
		i++;
	}
	else if (i == 5)
	{
		buffer[i] = '\0';
		i = 0;
	}
}

void	get_size_string(unsigned char *one_char_binary_array)
{
	static int i;
	if(ft_strncmp((char*)one_char_binary_array, "00100000", 8) != 0)	// remplir avec des espaces pour incrémenter ft_strlen dans main
	{
		printf("(size) one_char_binary_array : [%s]\n", one_char_binary_array);
		buffer[i] = get_char_from_binary(one_char_binary_array);
		printf("\t\t\t\t\t\tNew buffer char >> [%c]\n", buffer[i]);
		i++;
	}
	else if((ft_strncmp((char*)one_char_binary_array, "00100000", 8) == 0) && (i < 5))		// 5 = buffer size sans le \0
	{
		printf("(size) one_char_binary_array : [%s]\n", one_char_binary_array);
		buffer[i] = get_char_from_binary(one_char_binary_array);							// remplir le buffer avec les espaces reçus
		printf("\t\t\t\t\t\tNew buffer char >> [%c]\n", buffer[i]);
		i++;
	}
	else if (i == 5)
	{
		buffer[i] = '\0';
	}
}
