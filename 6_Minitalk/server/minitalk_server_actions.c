#include "minitalk_server.h"

void	got_signal1(int signo, siginfo_t *info, void *other)	// Handler (can't change signature)
{
	(void)other;	// sinon -Werror me met une erreur (unused param)

	static int				bit_count;
	static unsigned char	one_char_binary_array[8];
	static int				client_PID;
	static int				first_pass;
	static bool				got_size = false;		// Check if norminette ok
	if(first_pass == 0)
	{
		client_PID = info->si_pid;
		write(1, "Sending first signal to client\n", 31);
		kill(client_PID, SIGUSR1);
		first_pass = 1;
		ft_memset(one_char_binary_array, 0, 8);	// Super important
	}
	if (bit_count == 8)
	{
		bit_count = 0;
		ft_memset(one_char_binary_array, 0, 8);	// Reset & clean - Super important
	}
	if (bit_count < 8)
	{
		if (signo == 10)
		{
			one_char_binary_array[bit_count] = '0';
		}
		else if (signo == 12)
		{
			one_char_binary_array[bit_count] = '1';
		}
		bit_count++;
	}
	if (bit_count == 8)
	{
		// write(1, "\t**** Handler 1 **** Char just received (to encrypt) : [", 56);
		// char this_one = get_char_from_binary(one_char_binary_array);
		// write(1, &this_one, 1);
		// write(1, "]\n", 2);
		if (got_size == false)
		{
			got_size = get_size_string(one_char_binary_array);
		}
		else
		{
			got_size = get_string(one_char_binary_array);
		}
	}
}

bool	get_size_string(unsigned char *one_char_binary_array)	// Appelée par handler
{
	static int i = 0;
	// char *c = ft_itoa(i);
	// write(1, c, ft_strlen(c));
	if(ft_strncmp((char*)one_char_binary_array, "00100000", 8) != 0)	// remplir avec des espaces pour incrémenter ft_strlen dans main
	{
		buffer[i] = get_char_from_binary(one_char_binary_array);
		// write(1, "\t\t--- Added in buffer : [", 25);
		// write(1, (const void *)&buffer[i], 1);
		// write(1, "]\n\n", 3);
	}
	else if((ft_strncmp((char*)one_char_binary_array, "00100000", 8) == 0) && (i < 5))		// 5 = buffer size sans le \0
	{
		buffer[i] = get_char_from_binary(one_char_binary_array);							// remplir le buffer avec les espaces reçus
		// write(1, "\t\t--- Added in buffer : [", 25);
		// write(1, (const void *)&buffer[i], 1);
		// write(1, "]\n\n", 3);
	}
	if (i == 4)
	{
		i = 0;
		return(true);
	}
	i++;
	return(false);
}

bool	get_string(unsigned char *one_char_binary_array)	// Appelée par handler
{
	static int i_bis;
	// write(1, ">> ET LA ??\n", 12);
	if(ft_strncmp((char*)one_char_binary_array, "00000000", 8) != 0)			// null terminator = fin de la string
	{
		unsigned char y = get_char_from_binary(one_char_binary_array);
		// write(1, &y, 1);
		buffer[i_bis] = y;
		// buffer[i_bis] = get_char_from_binary(one_char_binary_array);
		// write(1, "\t\t--- Added in buffer (string) : [", 34);
		// write(1, (const void *)&buffer[i_bis], 1);
		// write(1, "]\n\n", 3);
		i_bis++;
	}
	else if(ft_strncmp((char*)one_char_binary_array, "00000000", 8) == 0)	// Print + vider buffer quand on arrive à la fin de la string
	{
		// write(1, "END OF STRING FROM THIS CLIENT\n", 31);
		i_bis = 0;
		return(false);
	}
	return(true);
}
