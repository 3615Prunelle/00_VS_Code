#include <stdio.h>

int amount_n(char *s)
{
	int i = 0;
	int j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			j++;
			printf ("s[%i] = %c et j = %i\n", i, s[i], j);
		}
		i++;
	}
	return (j);
}

int main (void)
{
	char *s = "Test.\n";
	printf ("Test string : %s\n", s);
	
	int i = amount_n(s);
	printf ("Amount /n : %i\n", i);
    
    return (0);
}
