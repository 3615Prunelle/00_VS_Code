#include "push_swap.h"

/* Notes random
🔵 Count the amount of digits in the longuest number (max 10 - Biggest int = 2 147 483 647)
		this number will be the amount of times I repeat the radix sort operation
🟢 Option 1 : work with tables / arrays of int
			Pro : Easy access to every int			/ Cons : Hassle to shift/insert
🟣 	Option 2 : work with chained/linked lists (struct : int + pointer to struct (+ link to first/last?))
			Pro : Easier to shift/insert			/ Cons : Hassle to access elements in the middle
🟠

⬇️✅‼️⁉️Ⓜ️❓❌
*/

int	main(int argc, char **argv)
{
	int i = 0;
	int	array_size;
	long int *numbers_array; // Pour pouvoir ajouter MAX_INT à tous les nombres et gérer les négatifs
	numbers_array = NULL;

	if(argc < 2)
		clean_early_exit(ERROR_MESSSAGE_01, numbers_array, true);
	else if(argc == 2)			// long string OR only one number
	{
		if(is_numerical_only(argv[1]))
		{
			array_size = count_numbers(argv[1]);							// Ⓜ️✅ (ft_split)
			if(array_size == 1)
				clean_early_exit(ERROR_MESSSAGE_01, NULL, true);
			numbers_array = malloc(sizeof(long int) * array_size);				// ‼️Ⓜ️✅‼️
			numbers_array = string_to_int_array(argv[1], numbers_array);
		}
		else
			clean_early_exit(ERROR_MESSSAGE_02, NULL, true);				// Ⓜ️✅
	}
	else if(argc > 2)
	{
		i = 1;							// Attention, un des args sera a.out, donc on compte à partir du 1
		array_size = 0;
		while(argc > 1)					// Car on zappe le 1er param
		{
			if(is_numerical_only(argv[i]))
			{
				array_size++;			// How many args numbers ?
				argc--;
				i++;
				continue;
			}
			else
				clean_early_exit(ERROR_MESSSAGE_02, numbers_array, true);
		}
		numbers_array = malloc(sizeof(long int) * array_size);
		i = 0;
		while (i < array_size)
		{
			numbers_array[i] = ft_atol(argv[i+1]);
			i++;
		}
	}

	// mettre tous ces check-ups dans une fonction
	i = 0;
	while (i < array_size)
	{
		if (((numbers_array[i]) < (long int)INT_MIN) || ((numbers_array[i]) > (long int)INT_MAX))
			clean_early_exit(ERROR_MESSSAGE_03, numbers_array, true);
		i++;
	}

	if(is_number_repeat(numbers_array, array_size))
		clean_early_exit(ERROR_MESSSAGE_04, numbers_array, true);

	if(is_sorted(numbers_array, array_size))
		clean_early_exit(ERROR_MESSSAGE_05, numbers_array, true);

	algorithm_selection(numbers_array, array_size);

	return(0);
}
