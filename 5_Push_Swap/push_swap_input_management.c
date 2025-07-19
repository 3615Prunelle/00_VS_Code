#include "push_swap.h"

bool		is_numerical_only(char *s)
{
	int i = 0;

	while(s[i] != '\0')
	{
		if((s[i] >= '0' && s[i] <='9') || s[i] == '+' || s[i] == '-' || s[i] == ' ')
		{
			if ((s[i] == '+' || s[i] == '-') && !(s[i+1] >= '0' && s[i+1] <='9'))
			{
				clean_early_exit(ERROR_MESSSAGE_02, true);
			}
			i++;
			continue;
		}
		clean_early_exit(ERROR_MESSSAGE_02, true);
	}
	return(true);
}

int			count_numbers(char *s)
{
	int	count;
	count = 0;

	char	**strings_array;
 	strings_array = ft_split(s, ' ');

	int i = 0;
	while (strings_array[i] != NULL)
	{
		count++;
		i++;
	}
	return(count);
}
// ---- ⬇️ NB : Take the array as a param instead of declaring & malloc'ing it in the function (avoids mem leaks)
long int	*string_to_int_array(int count, char *s, long int *numbers_array)
{
	char	**strings_array;
 	strings_array = ft_split(s, ' ');

	int i = 0;

	while (strings_array[i] != NULL)
	{
		numbers_array[i] = ft_atol(strings_array[i]);
		i++;
	}
	return(numbers_array);
}

long int	ft_atol(char *s)
{
	long int	i;
	long int	tot;
	long int	sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (((s[i] >= 9) && (s[i] <= 13)) || (s[i] == ' '))
		i++;
	if ((s[i] == '+') || (s[i] == '-'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		tot = tot * 10 + s[i] - '0';
		i++;
	}
	if (((tot * sign) < INT_MIN) || ((tot * sign) > INT_MAX))
		clean_early_exit(ERROR_MESSSAGE_03, true);
	return (tot * sign);
}

bool		is_sorted(long int *numbers_array, int array_size)
{
	long int	lower_number;
	lower_number = INT_MIN;

	while((numbers_array) && (array_size > 0))
	{
		if(*numbers_array >= lower_number)
		{
			lower_number = *numbers_array;
			numbers_array++;
			array_size--;
			continue;
		}
		else
			return(false);
	}
	return(true);
}
