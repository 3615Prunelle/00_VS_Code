#include "push_swap.h"

int	main(int argc, char **argv)
{
	int i;
	int	*array_size;
	int *numbers_array;

	i = 0;
	array_size = NULL;
	numbers_array = NULL;
	if(argc < 2)
		clean_early_exit(ERROR_MESSSAGE_01, numbers_array, true);

	else if(argc == 2)			// long string OR only one number
	{
		numbers_array = two_argv(argv[1], numbers_array, &array_size);
	}
	else if(argc > 2)
	{
		numbers_array = above_two_argv(argv, argc, numbers_array, &array_size);
	}
	check_array(numbers_array, array_size);
	return(0);
}

int		*two_argv(char *string_input, int *numbers_array, int *array_size)
{
		if(is_numerical_only(string_input))
		{
			*array_size = count_numbers(string_input);						// Ⓜ️✅ (ft_split)
			if(*array_size == 1)
				clean_early_exit(ERROR_MESSSAGE_01, NULL, true);
			numbers_array = malloc(sizeof(int) * *array_size);				// ‼️Ⓜ️✅‼️
			numbers_array = string_to_int_array(string_input, numbers_array);
		}
		else
			clean_early_exit(ERROR_MESSSAGE_02, NULL, true);				// Ⓜ️✅
		return(numbers_array);
}

int		*above_two_argv(char **strings_input, int argc, int *numbers_array, int *array_size)
{
	int i;
	i = 1;							// Attention, un des args sera a.out, donc on compte à partir du 1
	*array_size = 0;
	while(argc > 1)					// Car on zappe le 1er param
	{
		if(is_numerical_only(strings_input[i]))
		{
			(*array_size)++;		// How many args numbers ?
			argc--;
			i++;
			continue;
		}
		else
			clean_early_exit(ERROR_MESSSAGE_02, numbers_array, true);
	}
	numbers_array = malloc(sizeof(int) * *array_size);
	i = 0;
	while (i < *array_size)
	{
		numbers_array[i] = ft_atol(strings_input[i+1]);
		i++;
	}
	return(numbers_array);
}

void	check_array(int *numbers_array, int array_size)
{
	int i;

	i = 0;
	while (i < array_size)
	{
		if (((numbers_array[i]) < INT_MIN) || ((numbers_array[i]) > INT_MAX))
			clean_early_exit(ERROR_MESSSAGE_03, numbers_array, true);
		i++;
	}

	if(is_number_repeat(numbers_array, array_size))
		clean_early_exit(ERROR_MESSSAGE_04, numbers_array, true);

	if(is_sorted(numbers_array, array_size))
		clean_early_exit(ERROR_MESSSAGE_05, numbers_array, true);

	struct_config(numbers_array, array_size);
}
