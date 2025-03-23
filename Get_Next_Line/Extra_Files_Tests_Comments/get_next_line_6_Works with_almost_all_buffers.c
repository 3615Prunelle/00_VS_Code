#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>
#include <limits.h>

int		n_counter(char *s);
char	*ft_strchr(const char *s, int c); //attention, fonction de base modifiee (mis i+1 pour ne pas compter le \n)
void	*ft_calloc(size_t nmemb, size_t size);
int		newline_index_check(char *buffer);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2); //modified the argument kind from const char to regular char
void	*ft_memcpy(void *dest, const void *srce, size_t siz);
char	*ft_strlcpy(char *dst, const char *src, size_t size);  // changed i into dest, so it returns a string instead of a size
char	*ft_substr(char const *s, unsigned int start, size_t len);

#define BUFFER_SIZE 21 //Buffers that don't work : 10 - 13 - 19 - 20 - 21 (very bad result) - 22 - Works with very big ones
//Idee si fonction trop longue : Faire une fonction par taille de buffer selon read return ?
char *get_next_line (int fd)
{
	static char *buffer; //penser a le free quand on a copie' les derniers chars, pour pouvoir read la suite
	ssize_t read_value; //signale erreurs avec des valeurs négatives (contrairement a size_t). Pas mise en statique mais semble garder la derniere valeur en memoire

	int index_buffer = 0;
	int index_ligne = 0;
	int index_leftover = 0;
	int compteur_de_n = 0;
	int n_check_index = 0;

	char *portion_A = ft_calloc (BUFFER_SIZE, sizeof(char));
	char *portion_B = ft_calloc (BUFFER_SIZE, sizeof(char));
	char *portion_C = ft_calloc (BUFFER_SIZE, sizeof(char));

	if (!buffer) //condition necessaire, sinon buffer supprime' au 2nd appel de GNL (alors qu'il peut contenir du contenu utile)
	{
		buffer = ft_calloc (BUFFER_SIZE, 1);
		read_value = read (fd, buffer, BUFFER_SIZE); //toujours read dans un if, en cas de tres grand buffer
		compteur_de_n = n_counter(buffer);
	}

	while (read_value > 0)
	{
		while (read_value == BUFFER_SIZE)
		{
			if (compteur_de_n >= 1) //au moins un \n
			{
				portion_C = buffer; //mis dans une variable pour pouvoir la cropper si beaucoup de lignes
				n_check_index = newline_index_check(portion_C);
				portion_B = ft_strlcpy(portion_B, portion_C, n_check_index+1); //mettre tous les char jusqu'au \n inclus dans portion_B (qui peut aussi etre la seule ligne a lire si 1er passage)
				portion_B = ft_strjoin(portion_A, portion_B); //si leftover de portion A
				portion_C = ft_strchr(portion_C, '\n');//ici il faut raccourcir portion_C : retirer la ligne qu'on s'apprete a return
				buffer = ft_calloc (BUFFER_SIZE, 1);//et la mettre dans le buffer apres l'avoir calloc? - pour l'avoir au prochain call s'il y a d'autres lignes dedans
				buffer = portion_C;
				return (portion_B); //return obligatoire car au moins un \n trouve'
			}
			else //pas de \n trouve' = on cumule les buffers
			{
				portion_A = ft_strjoin(portion_B, portion_A); //peuvent etre vides au premier passage mais pas au second
				portion_A = ft_strjoin(portion_A, buffer);
				read_value = read (fd, buffer, BUFFER_SIZE);
				compteur_de_n = n_counter(buffer);
			}
		}
		while (read_value < BUFFER_SIZE) //fin du doc, il y a donc au moins un \n (a la fin), possiblement d'autres
		//attention, ne plus utiliser read a partir d'ici, car on a atteint la fin du document
		{
			compteur_de_n = n_counter(buffer);
			if (compteur_de_n > 1) //si plus d'un \n
			{
				portion_C = buffer; //mis dans une variable pour pouvoir la cropper si beaucoup de lignes
				n_check_index = newline_index_check(portion_C);
				portion_B = ft_strlcpy(portion_B, portion_C, n_check_index+1); //mettre tous les char jusqu'au \n inclus dans portion_B (qui peut aussi etre la seule ligne a lire si 1er passage)
				portion_B = ft_strjoin(portion_A, portion_B); //si leftover de portion A
				portion_C = ft_strchr(portion_C, '\n');//ici il faut raccourcir portion_C : retirer la ligne qu'on s'apprete a return
				buffer = ft_calloc (BUFFER_SIZE, 1);//et la mettre dans le buffer apres l'avoir calloc? - pour l'avoir au prochain call s'il y a d'autres lignes dedans
				buffer = portion_C;
				return (portion_B); //return obligatoire car au moins un \n trouve'
			}
			else //un seul \n = fin du document
			{
				buffer = ft_substr (buffer, 0, read_value); //enlever chars residuels apres le dernier \n
				portion_A = ft_strjoin(portion_A, buffer); //recuperer ce qu'il reste eventuellement des precedents passages
				buffer = ft_calloc (1, 1); //because free(buffer) doesn't work for some reason
				read_value = 0;
				return (portion_A); //dernier return ever car EOD
			}
		}
	}
	return (NULL); // dernier return de la fonction : if (read_value <= 0) = rien a lire ou erreur

}

char	*ft_strlcpy(char *dst, const char *src, size_t size)
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
		return (dst); // changed i into dest, so it returns a string instead of a size
	}
	while (j < (size - 1) && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst); // changed i into dest, so it returns a string instead of a size
}
int		n_counter(char *buffer)
{
	int i = 0;
	int	counter = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
			counter++;
		i++;
	}
	return(counter);
}
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' || s[i] == (char)c)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i+1]); 					//mis i+1 pour ne pas compter le \n
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

	if(!str)
		return(0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char *s1, char *s2) //changed const char * into char because it was marked as an error
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	if (!s1)
		return (s2);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}
// 	nb_str = 0;
// 	is_new_word = 0;
// 	while (i <= (int)size_s)
// 	{
// 		if ((s[i] == c) || (s[i] == '\0'))
// 		{
// 			if (is_new_word == 1)
// 				nb_str++;
// 			is_new_word = 0;
// 		}
// 		if (s[i] != c)
// 			is_new_word = 1;
// 		i++;
// 	}
// 	return (nb_str);
// }

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
