#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 10 //etudier variable statique ou mettre les char apres \n si ligne est plus courte que buffer

char *get_next_line(int fd)
{
    char buffer[BUFF_SIZE] = {0};
    char *final;
    char *temp;
    int i = 0; //index buffer
    int j = 0; //index final
    int nb_read = BUFF_SIZE;

    while (nb_read == BUFF_SIZE) //tant que \n pas trouve' / ligne pas finie
    {
        nb_read = read(fd, buffer, BUFF_SIZE);

        temp = final; // ladresse de temp =  adresse de final, les 2 pointeurs pointent au meme endroit
        final = (char *) malloc ((j + BUFF_SIZE) * sizeof(char)); //malloc prend toujours un nouvel espace, il ne rallonge pas l'existant

        //mettre le contenu pointe' par temp dans finale en copiant les char un a un
        int z = 0;
        while (z < j)
        {
            final[z] = temp[z];
            z++;
        }

        i = 0;
        while (i < BUFF_SIZE) //copier chaque char de buffer vers final
        {
            final[j] = buffer[i];
            if (buffer[i] == '\n')
                return (final); //return de fin de ligne
            
 // pour debug           printf ("final[%d] = %c - Buffer[%d] = %c - final is : %s\n", j, final[j], i, buffer[i], final);
            
            //ne jamais incrementer ailleurs qu en fin de boucle, ici, indispensable de garder i et j ensemble car interdependants
            i++;
            j++;
        }
    }
    return (final); //return de fin de document
}

int main (void)
{
    int fd = open("testfile.txt", O_RDONLY);
 
    char *line = get_next_line(fd);
    printf ("%s", line);

    char *line2 = get_next_line(fd);
    printf ("%s", line2);

    return (0);
}

//read buffer as many times as needed till \n >> while
//final variable extensible >> malloc
//don't copy chars after \n >> return final variable avec \n
//free memory

//Reserve de Printf :

	printf ("Read done\n");
	printf ("Buffer : %s\n", buffer);
	printf ("Buffer size : %i\n", BUFF_SIZE);
	printf ("Read size : %li\n", read_size);
	printf ("Leftover (vide au 1er passage) : %s\n", leftover);
	printf ("Nombre de /n dans leftover : %i\n", nb_n_dans_leftover);
	printf ("At least 1 /n found in Leftover ! Exact amount : %i\n", amount_n(leftover));
	printf ("Leftover (suite du dernier buffer commençant par un /n + Potentiellement les lignes suivantes à trimmer) : %s\n", leftover);
	printf ("Leftover avec le /n tronqué + Potentiellement les lignes suivantes à trimmer : %s\n", leftover);
	printf ("Index du 1er /n (starting from [0]) dans leftover : %i\n", index_n);
	printf ("Trimmed leftover (sans /n au début, avec /n à la fin : %s\n", trimmed_leftover);
	printf ("Leftover qui ne devrait pas avoir changé : %s\n", leftover);
	printf ("************************* Main line : %s\n", main_line);
	printf ("Entrée dans la boucle while successful\n");
	printf ("Leftover string (null si pas de /n trouvé) : %s\n", leftover);
	printf ("Trimmed buffer : %s\n", trimmed_buffer);
	printf ("Trimmed leftover : %s\n", trimmed_leftover);

	return ("Inside loop return");
	return ("Inside loop return");
	return ("Outside loop return : EOD théoriquement");
