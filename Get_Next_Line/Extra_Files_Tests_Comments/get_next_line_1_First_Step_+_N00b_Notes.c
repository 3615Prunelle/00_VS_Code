#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>

//step 1	(OK) lire n bytes d'un doc et le mettre dans un buffer de n bytes
//step 2	(OK) creer une string et mettre le contenu du buffer dedans
//step 3	(OK) lire suite du doc et le mettre a la suite de la string
//step 4	(OK) creer une loop qui fait ca automatiquement mais qui s'arrete au \n et revoie la 1ere ligne
//step 5	(OK) creer loop dans main et reprendre au \n ou on s'etait arretes pour reprendre la prochaine ligne au bon endroit
//step 6	(OK) gerer les cas de /n a a fin du buffer
//step 7	gerer les cas de /n a au debut du buffer
//step 8	gerer les cas de EOD
//step 9	gerer les cas de buffer plus petits que la ligne, et plus grand (puis faire edge cases, buffer de 1 ou 1000, pas de fd, etc)
//step 10	mettre le fichier test en argument a la compilation plutot que dans la main, pour pouvoir en changer facilement

#define BUFFER_SIZE 4

void	*ft_calloc(size_t nmemb, size_t size);
int		is_return(char *buffer);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *srce, size_t siz);

	// if (read_return < 0)				//valeur neg = erreur
	// 	return (NULL);
	// if (read_return == 0)			//nothing read - reached EOF
	// 	return (NULL);					//return requested in subject
	// if (read_return < BUFFER_SIZE)	//means texte plus petit que buffer, ou something has been read and reached EOF
	// 	return (TBD);

char *get_next_line (int fd)
{
	char *buffer;
	buffer = malloc (BUFFER_SIZE); //penser a free le buffer quand done with it

	char *ligne_entiere;
	ligne_entiere = ft_calloc (BUFFER_SIZE + 1, sizeof(char)); //premiere initialisation pour eviter segfault dans 1er pass loop

	char *ligne_finale;

	ssize_t read_return; //ssize_t permet de signaler des erreurs avec des valeurs négatives, ce que size_t ne fait pas
	read_return = read (fd, buffer, BUFFER_SIZE); //read put text in buffer and returns a ssize_t

	static int index_return; //je le rends statique, pour garder la valeur en memoire au prochain rappel
	index_return = is_return(buffer); //0 si nada ou \n au debut - sinon l'index est retourne'

	while ((read_return == BUFFER_SIZE) && index_return == 0)	//tant qu'on a pas atteint EOD ni de \n
	{
		ligne_entiere = ft_strjoin(ligne_entiere, buffer); //malloc est fait dans strjoin - on met 1er buffer
		read_return = read (fd, buffer, BUFFER_SIZE); //lire 2eme buffer
		index_return = is_return(buffer); //sortir de la loop quand on un \n se trouve ds le buffer
		//mark the \n spot, and prepare to return line
		//garder ce qui se trouve apres \n
		//determiner \n comme sep char avec ft_split?
		//penser a la prochaine ligne qui doit commencer au bon endroit
		if (index_return != 0)
		{
			ligne_finale = malloc (sizeof(ligne_entiere) + index_return + 1); // + 1 car index n'est pas size
			ft_memcpy(ligne_finale, ligne_entiere, (sizeof(ligne_entiere) + index_return + 1)); //or memmove to handle overlapping?
			int i =  0;
			while (i <= index_return) // choisi <= pour copier le \n
			{
				ligne_finale[i + sizeof(ligne_entiere + 1)] = buffer[i]; //copie les char de buff 0 a buff[index return] a la suite de la ligne
				i++;
			}
			//mark buffer[index] where \n was found !!!!!! il faudra reprendre la pour la next line
		}
	}
	return (ligne_finale);
	//The returned line must end with '\n', except if EOD
}

int	is_return(char *buffer)
{
	int i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i); //si on trouve \n a buffer[0], on return 0 - Est-ce un probleme? test this later
		i++;
	}
	return(0);
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
	grand_final = get_next_line(file_descriptor);

	printf ("%s\n", grand_final);

	return (0);
}

