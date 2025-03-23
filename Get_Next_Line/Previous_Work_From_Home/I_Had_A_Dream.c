#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 40

int amount_n(char *s);
int	n_index(char *s);

char *get_next_line(int fd)
{
	int i = 0;
	static int call; //debug info only
	printf ("\n\n\n--------- Call %i ---------\n", call);
	
	static char *backup_mainline; //back up pour cumul normal - no need to put as static mais c'est pour éviter de gérer la mémoire pour l'instant
	static char *leftover; //c'est là qu'il faut mettre le leftover
	
	char *buffer = calloc (BUFF_SIZE, 1);
	ssize_t read_size;
	
	if (!leftover)
	{
		read_size = read (fd, buffer, BUFF_SIZE); //il ne faudrait read que si leftover est vide ? sinon ça read même si leftover a plusieurs lignes en attente, no good
		printf ("Read done\n");
	}

	
	printf ("Buffer : %s\n", buffer);
	printf ("Buffer size : %i\n", BUFF_SIZE);
	printf ("Read size : %li\n", read_size);
	printf ("Leftover (vide au 1er passage) : %s\n", leftover);
	
	char *main_line;
	main_line = calloc (BUFF_SIZE, 1);

	int nb_n_dans_leftover = amount_n(leftover);
	printf ("Nombre de /n dans leftover : %i\n", nb_n_dans_leftover);
	
	char *trimmed_leftover;
	
	if (amount_n(leftover) > 0) //on entre ici qu'à partir du 2ème call
	{
		//LATER : vérifier si qqch à mettre devant, à faire une fois que cette partie est fonctionelle avec buffer plus grand que doc
		printf ("At least 1 /n found in Leftover ! Exact amount : %i\n", amount_n(leftover));
		printf ("Leftover (suite du dernier buffer commençant par un /n + Potentiellement les lignes suivantes à trimmer) : %s\n", leftover);
		leftover++; //supprime le premier \n - a du sens seulement s'il y a une ligne apres le \n - tester dans un if si ça pause problème
		printf ("Leftover avec le /n tronqué + Potentiellement les lignes suivantes à trimmer : %s\n", leftover);
		int index_n = n_index(leftover);
		printf ("Index du 1er /n (starting from [0]) dans leftover : %i\n", index_n);
		trimmed_leftover = calloc (BUFF_SIZE, 1);
		trimmed_leftover = strncpy(trimmed_leftover, leftover, index_n+1); //+1 car l'index ne représente pas le nombre de caractères à copier, car il commence à 0
		printf ("Trimmed leftover (sans /n au début, avec /n à la fin : %s\n", trimmed_leftover);
		printf ("Leftover qui ne devrait pas avoir changé : %s\n", leftover);
		printf ("************************* Main line : %s\n", main_line);
		main_line = strcat (main_line, trimmed_leftover); //Not sure about that line
		printf ("************************* Main line after cat : %s\n", main_line);
		call++;
		return (main_line);
	}
	
	while (read_size > 0) // = il y a / reste des trucs a lire
	{
		printf ("Entrée dans la boucle while successful\n");
		//char *search_ptr;						//no need anymore cette ligne et la suivante ? TBC
		//search_ptr = calloc (BUFF_SIZE, 1);
		if (!leftover)
		{
			leftover = calloc (BUFF_SIZE, 1);
			leftover = memchr(buffer, '\n', BUFF_SIZE); //s'il y a au moins un \n dans le buffer, cette variable pointe désormais sur le 1er \n trouvé dans le buffer et le garde en mémoire
			printf ("Leftover string (null si pas de /n trouvé) : %s\n", leftover);
		}
			
		if (leftover) // AU MOINS un retour à la ligne trouvé car memchr n'a pas retourné 0
		{
			int index_n = n_index(buffer);
			printf ("Index du 1er /n (starting from [0]) dans buffer : %i\n", index_n);
			char *trimmed_buffer = calloc (BUFF_SIZE, 1);
			trimmed_buffer = strncpy(trimmed_buffer, buffer, index_n+1); //+1 car l'index ne représente pas le nombre de caractères à copier, car il commence à 0
			printf ("Trimmed buffer : %s\n", trimmed_buffer);
			main_line = strcat (main_line, trimmed_buffer);
			if (call > 0) //a partir du 2ème call, on met ensemble le leftover et la main line
				main_line = strcat (leftover, main_line);
			call++;
			//il faut maintenant raccourir la premiere partie de leftover, avant le prochain rappel
			trimmed_leftover = memchr(leftover, '\n', BUFF_SIZE);
			printf ("Trimmed leftover : %s\n", trimmed_leftover);
			call++;
			return (main_line);
			//joindre main_line et buffer tronqué si c'est le début du document
			//si on quelque chose dans leftover, il faut le tronquer garder juste le debut jusqu au premier n et y ajouter main_ligne a la suite, puis return
		}
		else if (read_size == BUFF_SIZE) //pas de retour a la ligne détecté + texte a garder
		{
			backup_mainline = main_line; //utile dès le 2nd passage dans la loop
			printf ("Backup main line : %s\n", backup_mainline);
			main_line = calloc (BUFF_SIZE + (BUFF_SIZE * i), 1);
			main_line = strcat (backup_mainline, buffer); //on accumule les buffer sans \n
			printf ("************************* Main line : %s\n", main_line);
			read_size = read (fd, buffer, BUFF_SIZE); //lire seulement apres sécurisé une string
			continue;
		}
		else //pas de retour a la ligne détecté mais derniere lecture a la fin du doc
		{
			return ("Inside loop return");
		}
		i++;
		call++;
		return ("Inside loop return");
	}
	call++;
	return ("Outside loop return : EOD théoriquement");
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
