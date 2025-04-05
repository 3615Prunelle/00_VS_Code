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

	// file_descriptor = 42;
	// file_descriptor = 0;
	// file_descriptor = open ("Invalid File Descriptor", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_empty",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_nl",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_42_char_no_nl",
	// 				O_RDONLY);
	//file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_42_char_with_nl",
	//				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_multiple_line_no_nl",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_multiple_line_with_nl",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_multiple_nlx5",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_alternate_line_nl_no_nl",
	// 				O_RDONLY);
	 file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_alternate_line_nl_with_nl",
					O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_VS_Code/Get_Next_Line/TestFile_big_line_no_nl",
	// 				O_RDONLY);
	// file_descriptor = open("/home/schappuy/francinette/tests/get_next_line/gnlTester/files/big_line_with_nl",
	// 				O_RDONLY);
	// file_descriptor = open ("/home/schappuy/francinette/tests/get_next_line/fsoares",
	// 				O_RDONLY);
	// file_descriptor = open ("1char", O_RDONLY);

	line_number = 1;
	grand_final = ft_calloc(1, 1);
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
