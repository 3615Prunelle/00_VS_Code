#include <stdio.h>
#include <string.h>
int main()
{
   char lettre;
   int nbLignes, nbFois = 0;
   scanf("%c\n", &lettre);
   scanf("%d\n", &nbLignes);
   for (int idLigne = 0; idLigne < nbLignes; idLigne = idLigne + 1)
   {
      char ligne[1001];
      scanf("%[^\n]\n", ligne);
      int longueurLigne = strlen(ligne);
      for (int idLettre = 0; idLettre < longueurLigne; idLettre = idLettre + 1)
      {
         if (ligne[idLettre] == lettre)
         {
            nbFois = nbFois + 1;
         }
      }
   }
   printf("%d", nbFois);
}
