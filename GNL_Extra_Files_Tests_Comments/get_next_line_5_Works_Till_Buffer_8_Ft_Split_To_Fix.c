#include <unistd.h> // Read & Open
#include <fcntl.h> //necessary for the flags that are passed as arguments in 'open'
#include <stdlib.h>  // Malloc / Free
#include <stdio.h>
#include <limits.h>

int		n_counter(char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		newline_index_check(char *buffer);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *srce, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// char			**ft_split(const char *s, char c);
// static void		ft_init(int *i, int *idx_fnl, int *sub_beg, int *is_new_word);
// static void		ft_let_it_gooo(char **array_of_arrays, int nbr_elements);
// static void		ft_final(char **arrays, const char *s, char c, size_t size_s);
// static int		ft_count_str(const char *s, char c, size_t size_s);

#define BUFFER_SIZE 59 // 8 is the last functional size - Output fucked up from size 9

//step 5	(OK) creer loop dans main et reprendre au \n ou on s'etait arretes pour reprendre la prochaine ligne au bon endroit
//step 6	(OK) gerer les cas de /n a a fin du buffer
//step 7	(OK) gerer les cas de /n a au debut du buffer
//step 8	(OK) gerer les cas de EOD
//step 9	gerer les cas de buffer plus grands que la ligne (puis faire edge cases, buffer de 1 ou 1000, pas de fd, etc)
//step 10	mettre le fichier test en argument a la compilation plutot que dans la main, pour pouvoir en changer facilement

char *get_next_line (int fd)
{
	char *buffer; //semble garder les donnees a chaque appel meme si pas en statique - a cause de read?
	char *backup_buffer = buffer; //back_up du previous buffer avant malloc/read, utile a partir du 2eme appel?
	buffer = malloc (BUFFER_SIZE);

	ssize_t read_value; //ssize_t permet de signaler des erreurs avec des valeurs négatives, ce que size_t ne fait pas.
						//Pas mise en statique mais semble garder la derniere valeur en memoire
						//en revanche, valeur poubelle avant d'etre initialisee
	read_value = read (fd, buffer, BUFFER_SIZE);

	char *ligne_complete;
	char *backup_ligne_complete = ligne_complete;  //back_up avant calloc de la boucle, check si reste le meme
	char *ligne_finale;
	static int ft_split_counter = 0;

	if (ft_split_counter == 0) //changer la ref, j'ai mis ca pour faire un test car backup doit etre a 0 au premier passage
		backup_buffer = ft_calloc (BUFFER_SIZE, sizeof(char));

	int n_check_index;
	static char *crop_end; //maybe not necessary anymore since I have a pointer to first buffer

	if (read_value > 0)
	{
		ligne_complete = ft_calloc (BUFFER_SIZE, sizeof(char)); //la valeur reste dans le backup
		ligne_complete = ft_strdup(buffer); //le 1er buffer est mis dans la ligne

		while (read_value == BUFFER_SIZE) //ok dans tous les cas on check apres s'il y a un \n, il peut y en avoir 0, 1 ou ++++
		{
			n_check_index = newline_index_check(ligne_complete);
			if (n_check_index == 0)								//pas de \n = on read la suite et on ajoute
			{
				read (fd, buffer, BUFFER_SIZE);
				ligne_complete = ft_strjoin (ligne_complete, buffer); //fait malloc a chaque ajout
				backup_ligne_complete = ligne_complete;
			}
			if (n_check_index > 0) // 1er passage : on trouve au moins un \n = on garde les char juqu'a l'index du 1er \n
			{						//2eme passage : attention il y a deja qqch dans la ligne complete
				ligne_finale = malloc (sizeof(ligne_complete));
				ft_strlcpy(ligne_finale, ligne_complete, n_check_index+1); // ligne complete garde tous les char apres le \n
																			//ligne finale a ce qu'on veut
																			//si 2eme passage, manque qqch?
				n_check_index = newline_index_check(backup_buffer);
				//mettre ce qu'il a apres le \n dans le buffer precedent (ne marche pas s'il y a plusieurs \n though)
				if (backup_buffer)
					ligne_finale = ft_strjoin(&backup_buffer[n_check_index], ligne_finale);
					//retirer ce qu'il y a en position [0] a [n_index_check] dans le buffer
				ft_split_counter = 1;
				return (ligne_finale);
			}
		}
		while (read_value < BUFFER_SIZE) //on est arrives a EOD. 2 cas de figure : on a une ligne ou plusieurs
		{
			int n_count = n_counter(buffer);
			if (n_count == 1) //on est a la fin du doc et c'est la derniere/seule ligne
			{
				n_check_index = newline_index_check(backup_buffer);
				ligne_finale = ft_strjoin(&backup_buffer[n_check_index], buffer);
				return (ligne_finale);
			}
			// else if (n_count > 1)
			// {
			// 	char **test = ft_split(buffer, '\n'); //returns array of arrays - on doit retourner uniquement 1ere ligne puis 2eme apres 2eme appel
			// 	return (test[ft_split_counter]);

			// 	ft_split_counter++;
			// 	n_count--;
			// 	//attention au 2eme appel, read value sera 0, donc mettre une condition dans le 1er if || n_count > 0
			// }
			else //si 0 retour a la ligne dans le doc - Possible ?
				return (0);
		}
	}
	else
		return(0);
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
	dst[j] = '\0';
	return (i);
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

	if(!str)
		return(0);
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
	if (!s1)
		return(s2);
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

// char	**ft_split(const char *s, char c)
// {
// 	int		nb_str;
// 	char	**array_of_arrays;
// 	nb_str = ft_count_str(s, c, ft_strlen(s));
// 	array_of_arrays = ft_calloc ((nb_str + 1), sizeof (char *));
// 	if (!array_of_arrays)
// 		return (0);
// 	ft_final(array_of_arrays, s, c, ft_strlen(s));
// 	if (!array_of_arrays[0] && nb_str > 0)
// 	{
// 		free(array_of_arrays);
// 		return (NULL);
// 	}
// 	return (array_of_arrays);
// }

// static void	ft_init(int *i, int *idx_fnl, int *sub_beg, int *is_new_word)
// {
// 	*i = -1;
// 	*idx_fnl = -1;
// 	*sub_beg = 0;
// 	*is_new_word = 0;
// }

// static void	ft_let_it_gooo(char **array_of_arrays, int nbr_elements)
// {
// 	while (nbr_elements > 0)
// 	{
// 		free (array_of_arrays[nbr_elements - 1]);
// 		array_of_arrays[nbr_elements - 1] = NULL;
// 		nbr_elements--;
// 	}
// }

// static void	ft_final(char **arrays, const char *s, char c, size_t size_s)
// {
// 	int	i;
// 	int	idx_fnl;
// 	int	sub_beg;
// 	int	is_new_word;
// 	ft_init(&i, &idx_fnl, &sub_beg, &is_new_word);
// 	while (++i <= (int)size_s)
// 	{
// 		if ((s[i] == c) || (s[i] == '\0'))
// 		{
// 			if (is_new_word == 1)
// 			{
// 				arrays[++idx_fnl] = ft_substr(s, sub_beg, i - sub_beg);
// 				if (!arrays[idx_fnl])
// 					return (ft_let_it_gooo(arrays, idx_fnl));
// 			}
// 			is_new_word = 0;
// 		}
// 		if (s[i] != c)
// 		{
// 			if (is_new_word == 0)
// 				sub_beg = i;
// 			is_new_word = 1;
// 		}
// 	}
// }

// int	ft_count_str(const char *s, char c, size_t size_s)
// {
// 	int	i;
// 	int	nb_str;
// 	int	is_new_word;
// 	i = 0;
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
