#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>

#define BUFFER_SIZE 4

void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *srce, size_t size);
size_t	ft_strlen(const char *str);

char *get_next_line (int fd)
{
	char *buffer;
	buffer = malloc (BUFFER_SIZE);

	char *ligne_entiere1;
	char *ligne_entiere2;
	ligne_entiere2 = ft_calloc (BUFFER_SIZE, sizeof(char)); //not sure if useful, for the first pass in the loop ?

	ssize_t read_return; //ssize_t permet de signaler des erreurs avec des valeurs négatives
//	read_return = read (fd, buffer, BUFFER_SIZE); //read put text in buffer and returns a ssize_t
	read_return = BUFFER_SIZE; //for test purposes only

	int nb_buffer_dans_ligne = 0;
	int i = 0;

//dans la boucle, sauvegarder contenu precedent avant chaque malloc
//pour ca, mettre contenu dans variable1 de la bonne taille
//malloc + read_return de variable2
//mettre variable1 dans variable2
//ajouter contenu du buffer a la suite (strcat ?)

//puis faire l'inverse:

//malloc + read_return de variable1
//mettre variable2 dans variable1
//ajouter contenu du buffer a la suite (strcat ?)

	while (read_return == BUFFER_SIZE)	//full buffer
	{
		//i = 0;
		read_return = read (fd, buffer, BUFFER_SIZE);
		ligne_entiere1 = ft_calloc ((read_return + 1 + (BUFFER_SIZE * nb_buffer_dans_ligne)), sizeof(char));//+1 pour le null term required?
		ft_strlcpy(ligne_entiere1, ligne_entiere2, sizeof(ligne_entiere1));
		ft_strlcat(ligne_entiere1, buffer, sizeof(ligne_entiere1) + 1); //a priori, ici ligneentiere1 a tout ce qu'on veut dedans
		nb_buffer_dans_ligne++;
		// while ((buffer[i] != '\n') && (i < BUFFER_SIZE))
		// {
		// 	ligne_entiere1[i] = buffer[i];
		// 	i++;
		// }
		read_return = read (fd, buffer, BUFFER_SIZE);	//lit automatiquement la suite, mais ligne_entiere1 ne devrait pas bouger
		ligne_entiere2 = ft_calloc ((read_return + 1 + (BUFFER_SIZE * nb_buffer_dans_ligne)), sizeof(char));
		ft_strlcpy(ligne_entiere2, ligne_entiere1, sizeof(ligne_entiere2));
		ft_strlcat(ligne_entiere2, buffer, sizeof(ligne_entiere2) + 1); //pb de taille a resoudre, n'affiche pas le dernier char
		nb_buffer_dans_ligne++;
	}

	//int i = 0;
	// // prochaine etape a mettre quelque part

	return (ligne_entiere1);
}

int	main (void)
{
	const char *path_to_file = "/home/schappuy/00_VS_Code/Get_Next_Line/testdoc.txt";
	int file_descriptor = open (path_to_file, O_RDONLY); // Return open : file descriptor (small nonnegative int)

	char *grand_final;
	grand_final = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	grand_final = get_next_line(file_descriptor);

	grand_final[BUFFER_SIZE + 1] = '\0';
	printf ("%s\n", grand_final);

// note : chaque fois que j'appelle gnl (meme dans un printf), ca lit automatiquement la suite

	return (0);
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
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (size == 0)
	{
		return (i);
	}
	while (j < (size - 1) && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	//dst[j] = '\0';
	return (i);
}

size_t	ft_strlcat(char *dest, const char *srce, size_t size) //faire en sorte que size_t soit la longueur de la str finale
{
	size_t	i;
	size_t	length_s;
	size_t	length_d;

	i = 0;
	length_s = ft_strlen(srce);
	length_d = ft_strlen(dest);
	if (size <= length_d)
		return (size + length_s);
	while ((srce[i] != '\0') && (length_d + i < size - 1))
	{
		dest[length_d + i] = srce[i];
		i++;
	}
	//dest[length_d + i] = '\0';
	return (length_d + length_s);
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
