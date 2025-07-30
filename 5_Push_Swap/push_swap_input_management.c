#include "push_swap.h"

bool	is_numerical_only(char *s)
{
	int i = 0;

	while(s[i] != '\0')
	{
		if((s[i] >= '0' && s[i] <='9') || s[i] == '+' || s[i] == '-' || s[i] == ' ')
		{
			if ((s[i] == '+' || s[i] == '-') && !(s[i+1] >= '0' && s[i+1] <='9'))
			{
				return(false);
			}
			i++;
			continue;
		}
		return(false);
	}
	return(true);
}

int		count_numbers(char *s)
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
	i = 0;
	while(i < count)
	{
		free(strings_array[i]);		// alloué dans ft_split
		i++;
	}
	free(strings_array);			// alloué dans ft_split
	return(count);
}

int		*string_to_int_array(char *s, int *numbers_array)
{
	char	**strings_array;
 	strings_array = ft_split(s, ' ');

	int i = 0;

	while (strings_array[i] != NULL)	// Car ft_split a mis un \0 à la dernière array
	{
		numbers_array[i] = ft_atol(strings_array[i]);
		i++;
	}

	i = 0;
	while(strings_array[i] != NULL)
	{
		free(strings_array[i]);
		i++;
	}
	free(strings_array);
	return(numbers_array);
}

int		ft_atol(char *s)
{
	int	i;
	int	tot;
	int	sign;

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
	return (tot * sign);
}

bool	is_sorted(int *numbers_array, int array_size)
{
	int	highest_number;
	highest_number = INT_MIN;

	while((numbers_array) && (array_size > 0))
	{
		if(*numbers_array >= highest_number)
		{
			highest_number = *numbers_array;
			numbers_array++;
			array_size--;
			continue;
		}
		else
			return(false);
	}
	return(true);
}
