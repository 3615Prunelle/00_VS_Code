// #include "push_swap.h"
#include<stdio.h>
#include<stdbool.h>

#define SIZE 8	// 4 dans a + 4 dans b

bool	is_empty(int array[])		// Not good car on ne peut pas avoir plusieurs 0
{
	int i = 0;
	while(i < SIZE)
	{
		if(array[i] != 0)
			return(false),
		i++;
	}
	return(true);
}

bool	is_number_repeat(int array[])
{
	int i = 0;
	int j;
	int count_occurences;

	while(i < SIZE)
	{
		j = 0;
		count_occurences = 0;			// Reset pour chaque nombre
		while (j < SIZE)
		{
			if(array[i] == array[j])
			{
				count_occurences++;
					if(count_occurences > 1)
						return(true);
			}
			j++;
		}
		i++;
	}
	return(false);
}

void	swap_a(int array_a[])	// ✅
{
	int	temp;

	if((array_a[0] != '\0') || (array_a[1] != '\0'))
	{
		temp = array_a[0];
		array_a[0] = array_a[1];
		array_a[1] = temp;
	}
}

void	swap_b(int array_b[])	// ✅
{
	int	temp;

	if((array_b[0] != '\0') || (array_b[1] != '\0'))
	{
		temp = array_b[0];
		array_b[0] = array_b[1];
		array_b[1] = temp;
	}
}

void	swap_a_and_b(int array_a[], int array_b[])
{
	swap_a(array_a);
	swap_b(array_b);
}
void	push_a(int array_a[], int array_b[])
{
	/*Take the first element at the top of b and put it at the top of a.
	Do nothing if b is empty.*/

	if(array_b[0] == )
	int i = SIZE;
	while (i >= 2)						// Put every number at index i+1, starting by the end
	{
		array_a[i-1] = array_a[i-2];	// i=8 --- array_a[7] (last) prend array_a[6]
		i--;							// i=2 --- array_a[1] (second) prend array_a[0] (first)
	}

	array_a[0] = array_b[0];			// First of b goes to top of a


	i = 0;								// Now, update b : put every number at i-1
	while (i <= 6)
	{
		array_b[i] = array_b[i+1];		// i=0 --- array_b[0] (first) prend array_b[1]
		i++;							// i=6 --- array_b[6] (first) prend array_b[7] (last)
	}
	array_b[i+1] = 0;
}

int		main(void)
{
	int a[SIZE] = {0, 444, 874, 6, 7, 8, 11, 10};
	int b[SIZE] = {1, 456, 92, 789, 2, 3, 4, 5};

	if(is_number_repeat(a) || is_number_repeat(b))
	{
		ft_printf("Duplicated number, edit and try again !\n");
		return(1);
	}

	int i = 0;
	ft_printf("\nIndex :		0	1	2	3	4	5	6	7\n");
	ft_printf("array_a :	");
	while (i < SIZE)
	{
		ft_printf("%i	", a[i]);
		i++;
	}
	i = 0;
	ft_printf("\narray_b :	");
	while (i < SIZE)
	{
		ft_printf("%i	", b[i]);
		i++;
	}
	ft_printf("\n\n");
	return(0);
}

/*
🟡 sa (swap a): Swap the first 2 elements at the top of stack a.
	Do nothing if there is only one element or none.
🟡 sb (swap b): Swap the first 2 elements at the top of stack b.
	Do nothing if there is only one element or none.
🟡 ss : sa and sb at the same time.
🟡 pa (push a): Take the first element at the top of b and put it at the top of a.
	Do nothing if b is empty.
🟡 pb (push b): Take the first element at the top of a and put it at the top of b.
	Do nothing if a is empty.
🟡 ra (rotate a): Shift up all elements of stack a by 1.
	The first element becomes the last one.
🟡 rb (rotate b): Shift up all elements of stack b by 1.
	The first element becomes the last one.
🟡 rr : ra and rb at the same time.
🟡 rra (reverse rotate a): Shift down all elements of stack a by 1.
🟡 The last element becomes the first one.
🟡 rrb (reverse rotate b): Shift down all elements of stack b by 1.
	The last element becomes the first one.
🟡 rrr : rra and rrb at the same time.
*/
