#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>

//step 5	(OK) creer loop dans main et reprendre au \n ou on s'etait arretes pour reprendre la prochaine ligne au bon endroit
//step 6	(OK) gerer les cas de /n a a fin du buffer
//step 7	(FAIL) gerer les cas de /n a au debut du buffer
//step 8	gerer les cas de EOD
//step 9	gerer les cas de buffer plus petits que la ligne, et plus grand (puis faire edge cases, buffer de 1 ou 1000, pas de fd, etc)
//step 10	mettre le fichier test en argument a la compilation plutot que dans la main, pour pouvoir en changer facilement

#define BUFFER_SIZE 4

char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		newline_index_check(char *buffer);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *srce, size_t siz);

	// if (read_value < 0)				//valeur neg = erreur
	// 	return (NULL);
	// if (read_value == 0)				//nothing read - reached EOF
	// 	return (NULL);					//return requested in subject
	// if (read_value < BUFFER_SIZE)	//means texte plus petit que buffer, ou something has been read and reached EOF
	// 	return (TBD);

char *get_next_line (int fd)
{
	//static int flag_2nd_call;

	static char *buffer; //mis en static pour que le derniere lecture soit gardee
	char *temp_leftover;
	char *leftover;

	if (!buffer) //before it was if (flag_2nd_call == 0), bus bonus if only 1 static var
		buffer = malloc (BUFFER_SIZE); //fait comme ca sinon supprime tout au 2nd appel de GNL

	char *ligne_entiere;
	ligne_entiere = ft_calloc (BUFFER_SIZE + 1, sizeof(char)); //premiere initialisation pour eviter segfault dans 1er pass loop

	char *ligne_finale;

	ssize_t read_value; //ssize_t permet de signaler des erreurs avec des valeurs négatives, ce que size_t ne fait pas

	//!!!!!!!!!!!!!! the line below is a problem if \n is at buffer[0], use debugger here for more info. Trying an alternative solution.
	read_value = read (fd, buffer, BUFFER_SIZE); //read put text in buffer and returns a ssize_t

	static int index_newline; //je le rends statique, pour garder la valeur en memoire au prochain rappel
	index_newline = newline_index_check(buffer); //0 si nada ou \n au debut - sinon l'index est retourne'

	while ((read_value == BUFFER_SIZE) && index_newline == 0)	//tant qu'on a pas atteint EOD ni de \n
	{
		ligne_entiere = ft_strjoin(ligne_entiere, buffer); //malloc est fait dans strjoin - on met 1er buffer
 		read_value = read (fd, buffer, BUFFER_SIZE); //lire 2eme buffer
		index_newline = newline_index_check(buffer); //sortir de la loop quand on un \n se trouve ds le buffer

		if (index_newline > 0)
		{
			//int size = sizeof(ligne_entiere); DELETE
			ligne_finale = malloc (sizeof(ligne_entiere) + index_newline + 2); // + 2 car commence a 1 + \0
			ft_memcpy(ligne_finale, ligne_entiere, (sizeof(ligne_entiere) + index_newline + 2)); //or memmove to handle overlapping?
			int i =  0;
			while (i <= index_newline)
			{
				ligne_finale[i + sizeof(ligne_entiere + 1)] = buffer[i];
				i++;
				if (index_newline == 1)
					return (ligne_finale);
			}
		}
	}
	// if (flag_2nd_call == 1)  //je pensais que cette condition etait necessaire mais en fait non, ca marche tres bien sans
	// {
	// 	char *from_2nd_line = ft_strjoin(leftover, ligne_finale);
	// 	return (from_2nd_line);
	// }

	//flag_2nd_call = 1;
	return (ligne_finale); //ISSUE - The return for the 1st line includes characters after \n. Looks ok on the output but wrong.
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' || s[i] == (char)c)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}
int	newline_index_check(char *buffer)
{
	int i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1); //car problemes si on commence a 1 (buffer[0] n'est pas lu) et si on trouve \n a buffer[0] avec retour 0
		i++;
	}
	return(0); // -1 pas possible dans le return car match une variable statique dans fonction GNL
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc (nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
char	*ft_strdup(const char *s)
{
	char	*newstring;
	size_t	i;

	i = 0;
	newstring = malloc ((ft_strlen(s) + 1) * sizeof (char));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		newstring[i] = s[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 [j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
void	*ft_memcpy(void *dest, const void *srce, size_t siz)
{
	size_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_srce;

	if (!dest && !srce)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_srce = (const unsigned char *)srce;
	i = 0;
	while (i < siz)
	{
		ptr_dest[i] = ptr_srce[i];
		i++;
	}
	return (dest);
}

int	main (void)
{
	const char *path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/testdoc.txt";
	int file_descriptor = open (path_to_file, O_RDONLY); // Return open : file descriptor (small nonnegative int)

	char *grand_final;

	int i = 0;

	while (i < 20) //for test purposes only, trouver le moyen de s'arreter quand fin du doc atteint.
	{
		grand_final = get_next_line(file_descriptor);
		printf ("%s", grand_final);
		i++;
	}

	return (0);
}

