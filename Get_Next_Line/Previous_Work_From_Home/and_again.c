#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 20

int	n_index(char *s);

char *get_next_line(int fd)
{
	int i = 0;
	static int call; //debug info only
	printf ("\n\n\n--------- Call %i ---------\n", call);
	
	char *buffer = calloc (BUFF_SIZE, 1);
	ssize_t read_size = read (fd, buffer, BUFF_SIZE);
	printf ("Buffer : %s\n", buffer);
	printf ("Buffer size : %i\n", BUFF_SIZE);
	printf ("Read size : %li\n", read_size);
	
	char *main_line;
	main_line = calloc (BUFF_SIZE, 1);
	
	static char *backup_mainline; //back up pour cumul normal - no need to put as static mais c'est pour éviter de gérer la mémoire pour l'instant
	static char *leftover; //c'est là qu'il faut mettre le leftover
	
	while (read_size > 0) // = il y a / reste des trucs a lire
	{
		printf ("Entrée dans la boucle successful\n");
		//char *search_ptr;						//no need anymore cette ligne et la suivante ? TBC
		//search_ptr = calloc (BUFF_SIZE, 1);
		if (!leftover)
		{
			leftover = memchr(buffer, '\n', BUFF_SIZE); //s'il y a au moins un \n dans le buffer, cette variable pointe désormais sur le 1er \n trouvé et le garde en mémoire
			printf ("Leftover value (null si pas de n trouvé) : %s\n", leftover);
		}
			
		if (leftover) // AU MOINS un retour à la ligne trouvé car memchr n'a pas retourné 0
		{
			//leftover++; //supprime le premier \n - a du sens seulement s'il y a une ligne apres le \n - tester dans un if si ça pause problème
			//!!!! ATTENTION, il peut y avoir plus d'une ligne dans cette variable leftover !!!!
			printf ("Leftover (suite du dernier buffer à partir de n + Potentiellement les lignes suivantes à trimmer) : %s\n", leftover);

			printf ("At least 1 new line char found !\n");
			printf ("Buffer : %s\n", buffer);
			//a ce stade, on théoriquement soit main_line avec les cumuls de buffer, soit c'est le 1er passage et on doit renvoyer ce qu'il y a jusqu'au \n
			//main_line is théoriquement ready to go
			//tronquer le buffer : ne garder que les caractères du début jusqu'au n inclus (le reste se trouve dans leftover)
			int index_n = n_index(buffer);
			printf ("Index du n : %i\n", index_n);
			char *trimmed_buffer = calloc (BUFF_SIZE, 1);
			trimmed_buffer = strncpy(trimmed_buffer, buffer, index_n+1); //+1 car l'index ne représente pas le nombre de caractères à copier, car il commence à 0
			printf ("Trimmed buffer : %s\n", trimmed_buffer);
			main_line = strcat (main_line, trimmed_buffer);
			if (call > 0)
				main_line = strcat (leftover, main_line);
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
    
    //char *line3 = get_next_line(fd);
    //printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 3 = %s", line3);
    
    //char *line4 = get_next_line(fd);
    //printf (">>>>>>>>>>>>>>>>>>>>>>>> Official Line 4 = %s", line4);

    return (0);
}
