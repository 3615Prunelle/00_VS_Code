/* USEFUL EMOJIS KIKOULOL
⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

#include "minitalk_server.h"

// void	got_signal(int signo, siginfo_t *info, void *other)	// Handler (can't change signature)
// {
// 	// vérif ce qu'il y a dans les param
// 	static int				i;
// 	static int				bit_count;
// 	static unsigned char	one_char_binary_array[8];
// 	static int				client_PID_int;
// 	static int				got_string_size;
// 	static size_t 			string_length;
// 	static int				got_string;

// 	client_PID_int = info->si_pid;

// 	if (bit_count == 8)
// 		bit_count = 0;
// 	else if (bit_count < 8)
// 	{
// 		if (signo == 10)
// 		{
// 			one_char_binary_array[bit_count] = '0';
// 		}
// 		else if (signo == 12)
// 		{
// 			one_char_binary_array[bit_count] = '1';
// 		}
// 		bit_count++;
// 	}
// 	if (bit_count == 8)	// tous les 8 signaux, appel de fonction selon le besoin
// 	{
// 		ft_printf("Bit count reached 8, about to take action :\t\t");
// 		if(got_string_size == 0)
// 		{
// 			ft_printf("... in 'get_size_string' function if\n");
// 			string_length = get_size_string(one_char_binary_array);
// 			// got_string_size = 1;			// Nope car peut avoir plusieurs chars
// 		}
// 	}
// }

// size_t	get_size_string(unsigned char *one_char_binary_array)
// {
// 	size_t	string_length;	// long unsigned int
// 	static unsigned char size_max_in_digits[5]; // max size_t = 65535 = 5 digits ---- Mettre un \0 à la fin ?

// 	static int i = 4;
// 	if(ft_strncmp(one_char_binary_array, "00000000", 8) != 0)
// 	{ // attention, on les recoit à partir du dernier
// 		size_max_in_digits[i] = get_int_from_binary(one_char_binary_array);
// 		i--;
// 	}
// 	if(ft_strncmp(one_char_binary_array, "00000000", 8) == 0)
// 	{
// 		string_length = ft_atoi(size_max_in_digits);
// 		volatile_number = string_length;
// 	}
// 	return(string_length);
// }

// int		get_string(size_t string_length, unsigned char *one_char_binary_array)
// {
// 		// PID Max = 4194304 (cmd shell : cat /proc/sys/kernel/pid_max) = 7 chars
// 		static unsigned char	client_PID_array[7];
// 		static int				i;
// 		char					char_to_convert;
// 		int						final_PID_number;

// 		char_to_convert = get_char_from_binary(one_char_binary_array);

// 		while(i < string_length)
// 		{
// 			client_PID_array[string_length - i] = char_to_convert;		// si le client envoie les chiffres à l'envers = win
// 			i++;
// 		}
// 		if (i == string_length)
// 		{
// 			final_PID_number = ft_atoi(client_PID_array);
// 			return(final_PID_number);
// 		}
// }
