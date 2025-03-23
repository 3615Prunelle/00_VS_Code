#include <stdio.h>
#include <string.h>

int main()
{
	char game1[52], game2[52];
	int i = 0;

	scanf("%s", game1);
	scanf("%s", game2);

	int size1 = strlen(game1);
	int size2 = strlen(game2);

	while ((i < size1) && (i < size2) && game1[i] == game2[i])
		i++;
	if (game1[i] == game2[i])
		printf("=\n");

	else if (i == size2 || (i < size1 && game1[i] < game2[i]))
		printf("1\n");
	 else
		printf("2\n");

	printf("%d\n", i);
}
