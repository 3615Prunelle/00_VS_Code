#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 3

int amount_n(char *s);
int	n_index(char *s);
char *ft_end_away(char *s);
char *ft_beg_away(char *s);

char *get_next_line(int fd)
{
// ------------------------------------------------------------------------- ** All ints declared below ** ------------------------------- //
	int i = 0;
	int nb_de_n;
	ssize_t read_size;
// --------------------------------------------------------------------------------- ** Debug info only ** ------------------------------ //
	static int call;
	call++;
	printf ("\n\n\n--------- Call %i ---------\n", call);
// ---------------------------------------------------------------------- ** All strings declared below ** ------------------------------ //
	char ligne = calloc (BUFF_SIZE, 1);
	char *buffer = calloc (BUFF_SIZE, 1);
	char *trimmed_beg = calloc (BUFF_SIZE, 1); // Va jusqu'à /n inclus
	static char *trimmed_end; // A partir du /n non inclus
// ------------------------------------------ ** Ne pas lire tant qu'il reste des char dans trimmed_end ** ------------------------------ //
	if (trimmed_end == (NULL))
	{
		read_size = read (fd, buffer, BUFF_SIZE);
		if (read_size <= 0)
			return (NULL);
		printf ("Read done and read size > 0\n");
		printf ("Read size : %li\n", read_size);
		printf ("Buffer : %s\n", buffer);
		trimmed_end = buffer;
		printf ("Trimmed end : %s\n", trimmed_end);
	}
// ------------------------------------------------------------- ** Check s'il y a un /n dans trim_beg and if so, return it ** ----------- //
	nb_de_n = amount_n(trimmed_beg);
	if (nb_de_n == 1)
		return(trimmed_beg);
// --------------------------------------------------------------- ** Si pas de /n, read le reste et cumuler jusqu'à trouver un /n ** ----------- //
	while (nb_de_n == 0)
	{
		read (fd, buffer, BUFF_SIZE);
		ligne = strcat (trimmed_beg, buffer);
		nb_de_n = amount_n(trimmed_beg);
	}
// ----------------------------------------------------------------- ** Si plus d'un /n, use trim functions and return trimmed_beg ** ----------- //	
	if (nb_de_n > 1)
	
	
	
	if (read_size >= 0)
	{
		trimmed_beg = ft_end_away(trimmed_end);
		printf ("Trimmed beg : %s\n", trimmed_beg);
		trimmed_end = ft_beg_away(trimmed_end);
		printf ("Trimmed end : %s\n", trimmed_end);
		
	}
	

	
	return ("Test return");
	
}

char *ft_end_away(char *s)
{
	int i = 0;
	char *new;
	new = calloc (sizeof(s), 1);
	
	while (s[i] != '\0')
	{
		if (s[i] != '\n')
			new[i] = s[i];
		else
		{
			new[i] = '\n';
			return(new);
		}
		i++;
	}
		return(s); //if no /n found, return original string
}
	
char *ft_beg_away(char *s)
{
	int i = 0, j = 0;
	char *new;
	new = calloc (sizeof(s), 1);
		
	while (s[i] != '\0')
	{
		if (s[i] != '\n')
			i++;
		else
		{
			i++; //on se place donc au char après le /n
			break; //sortie de boucle
		}
	}
	while (s[i] != '\0')
	{
		new[j] = s[i];
		i++;
		j++;
	}
	return(new);
	//return(s); //if no /n found, return original string
}

int amount_n(char *s)
{
	int i = 0;
	int j = 0;
	
	if (!s)
		return(0);
		
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

int	n_index(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1); // erreur
}

int main (void)
{
    int fd = open("testfile.txt", O_RDONLY);
 
    char *line1 = get_next_line(fd);
    printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 1 = %s", line1);

    char *line2 = get_next_line(fd);
    printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 2 = %s", line2);
    
    char *line3 = get_next_line(fd);
    printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 3 = %s", line3);
    
    char *line4 = get_next_line(fd);
    printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 4 = %s", line4);

    return (0);
}
