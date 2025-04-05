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
// ------------------------------------------------------------------------- ** Useful info to keep in mind ** ------------------------------- //

temp = final; // ladresse de temp =  adresse de final, les 2 pointeurs pointent au meme endroit
final = (char *) malloc ((j + BUFF_SIZE) * sizeof(char)); //malloc prend toujours un nouvel espace, il ne rallonge pas l'existant
i++, j++;  //ne jamais incrementer ailleurs qu en fin de boucle, ici, indispensable de garder i et j ensemble car interdependants
ssize_t read_value;  //signale erreurs avec des valeurs négatives (contrairement a size_t)

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
// ------------------------------------------------------------- ** Reserve de Printf ** ----------- //
	printf ("Read done\n");
	printf ("Buffer : %s\n", buffer);
	printf ("Buffer size : %i\n", BUFF_SIZE);
	printf ("Read size : %li\n", read_size);
	printf ("Leftover (vide au 1er passage) : %s\n", leftover);
	return ("Inside loop return");
	return ("Outside loop return");
// --------------------------------------------------------------- ** Si pas de /n, read le reste et cumuler jusqu'à trouver un /n ** ----------- //
	while (nb_de_n == 0)
	{
		read (fd, buffer, BUFF_SIZE);
		ligne = strcat (trimmed_beg, buffer);
		nb_de_n = amount_n(trimmed_beg);
	}
// ----------------------------------------------------------------- ** Si plus d'un /n, use trim functions and return trimmed_beg ** ----------- //	
	if (nb_de_n > 1)

