#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>
#include <limits.h>

char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		newline_index_check(char *buffer);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *srce, size_t siz);

#define BUFFER_SIZE 4 //Only works with buffers 4, 6, 7, 8

//step 5	(OK) creer loop dans main et reprendre au \n ou on s'etait arretes pour reprendre la prochaine ligne au bon endroit
//step 6	(OK) gerer les cas de /n a a fin du buffer
//step 7	(OK) gerer les cas de /n a au debut du buffer
//step 8	(OK) gerer les cas de EOD
//step 9	gerer les cas de buffer plus grands que la ligne (puis faire edge cases, buffer de 1 ou 1000, pas de fd, etc)
//step 10	mettre le fichier test en argument a la compilation plutot que dans la main, pour pouvoir en changer facilement

char *get_next_line (int fd)
{
	static char *buffer; //mis en static pour que le derniere lecture soit gardee
	ssize_t read_value; //ssize_t permet de signaler des erreurs avec des valeurs négatives, ce que size_t ne fait pas. Pas mise en statique mais semble garder la derniere valeur en memoire

	int index_buffer = 0;
	int index_ligne = 0;
	int index_leftover = 0;

	char *ligne_entiere = ft_calloc (BUFFER_SIZE, sizeof(char));
	char *ligne_finale = ft_calloc (BUFFER_SIZE, sizeof(char)); //calloc necessary if the buffer size is not full
	char *leftover = ft_calloc (BUFFER_SIZE, sizeof(char));

	if (!buffer) //fait comme ca sinon supprime tout au 2nd appel de GNL et qu'il reste quelque chose dans le buffer
	{
		read_value = BUFFER_SIZE; //pour rentrer dans la boucle
		buffer = ft_calloc (BUFFER_SIZE, 1);
	}
	else
	{
		leftover = ft_strchr(buffer, '\n'); //copier buffer from \n
		leftover++; //trim le \n but will lead to memory issues when using free
		leftover = ft_strdup(leftover);
	}

	while (read_value >= 0)
	{
		if (read_value == BUFFER_SIZE) //tant qu'on lit un full buffer qui nous interesse
		{
			read_value = read (fd, buffer, BUFFER_SIZE); //read put text in buffer and returns a ssize_t
			index_buffer = 0;
			ft_memcpy(ligne_entiere, ligne_finale, sizeof(ligne_finale));
			ligne_finale = ft_calloc (BUFFER_SIZE + (BUFFER_SIZE * index_buffer), sizeof(char)); //calloc in case of \n : return value de 4 mais en realite il y aura moins de char copies
			ft_memcpy(ligne_finale, ligne_entiere, sizeof(ligne_finale));
			while (index_buffer < BUFFER_SIZE)
			{
				if (buffer[index_buffer] != '\n')
					ligne_finale[index_ligne] = buffer[index_buffer];
				else if (buffer[index_buffer] == '\n')
				{
					ligne_finale[index_ligne] = buffer[index_buffer]; //on met le \n a la fin de chaque ligne avant de la renvoyer
					ligne_finale = ft_strjoin(leftover, ligne_finale);
					return(ligne_finale);
				}
				index_buffer++;
				index_ligne++;
			}
		}
		else
			return (NULL);
			// read_value < BUFFER_SIZE	texte plus petit que buffer = something has been read and reached EOF
			// read_value < 0				valeur neg = erreur
			// read_value == 0				nothing read - reached EOF (return requested in subject)
	}
	return(NULL); //si read_value <= 0
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' || s[i] == (char)c)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]); //i++ au lieu de i pour renvoyer le char apres \n ? Teste' mais issues
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

	grand_final = get_next_line(file_descriptor);
	printf ("%s", grand_final);

	while (grand_final != 0)
	{
		grand_final = get_next_line(file_descriptor);
		printf ("%s", grand_final);
		i++;
	}
	return (0);
}
