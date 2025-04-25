#include "get_next_line.h"

#define ROUQUINETTE_DEBUG
// pour lancer tester : comment out uniquement cette ligne au lieu de tout le reste en dessous
#ifdef ROUQUINETTE_DEBUG


#endif

void	freedom_yolo(void **mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

int	main(void)
{
	int		file_descriptor;
	int		line_number;
	char	*grand_final;

	file_descriptor = open ("/home/schappuy/00_VS_Code/1_Libft/ft_isalpha.c", O_RDONLY);

	line_number = 1;
	grand_final = ft_calloc_copy(1, 1);
	while (grand_final != (NULL))
	{
		freedom_yolo((void **)&grand_final);
		grand_final = get_next_line(file_descriptor);
		if (grand_final == NULL)
			break ;
		printf("[Line %i]	%s", line_number, grand_final);
		line_number++;
	}
	if (grand_final == (NULL))
		printf("[Line %i]	%s", line_number, grand_final);

	close(file_descriptor);
	if (!grand_final)
		printf("\n");
	freedom_yolo((void **)&grand_final);
	return (0);
}
