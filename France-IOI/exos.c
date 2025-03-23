#include <stdio.h>

void	rectangle(int lignes, int colonnes, char motif);
void	triangle(int lignes, char motif);

void	ligne(int longueur, char motif)
{
	for (int i = 0; i < longueur; i++)
		printf("%c", motif);
}

void	rectangle(int lignes, int colonnes, char motif)
{
	ligne(colonnes, motif);
	for (int i = 0; i < lignes - 2; i++)
	{
		printf("%c", motif);
		for (int j = 0; j < colonnes - 2; j++)
		{
			printf(" ");
		}
		printf("%c", motif);
		printf("\n");
	}
	ligne(colonnes, motif);
}
void	triangle(int lignes, char motif)
{
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < lignes; j++) //create a loop that is = amount of lines (lines = colomns)
		{
			printf("%c", motif); //print a @, because every line starts with a @
			for (int k = 0; k < lignes - 2; k++) //create a loop that is amount of lines - 2 (first and last don't coun't)
			{
				printf("???");//print 0 space (find/create a variable that worths 0) and another @
				//printf \n - Maybe the one below is well placed already
				//increase the amount of spaces at every pass in the loop, but not the @
			}
		}
		printf("\n");
	//use the ligne function for the last line (warning - keep that in the loop, because it will just be one line if input = 1)
	}
}

int	main()
{
	int nb_deX, nb_lign_rec, nb_col_rec, nb_lign_tri;
	scanf ("%d %d %d %d", &nb_deX, &nb_lign_rec, &nb_col_rec, &nb_lign_tri);

	ligne(nb_deX, 'X');
	printf("\n");
	rectangle(nb_lign_rec, nb_col_rec, '#');
	printf("\n");
	triangle(nb_lign_tri, '@');
	printf("\n");
}
