#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define RED "\e[1;31m"
# define CYAN "\e[1;36m"

int i = 0;

void *sandbox_thread(void *data)
{
	pthread_t	another_identifiant;			// Tester sans
	another_identifiant = pthread_self();
	printf("%si is [%d]\tIdentifiant is [%li] - About to sleep for 2 secs\n%s", MAGENTA, i, another_identifiant, NC);
	sleep(2);
	i++;
	printf("%si is [%d]\tIdentifiant is [%li] - Slept for 2 secs\n%s", MAGENTA, i, another_identifiant, NC);
	return (NULL);
}

int main(void)
{
	pthread_t	identifiant_1;
	pthread_t	identifiant_2;

	printf("%sFirst i is [%d]\n%s", YELLOW, i, NC);
// A partir de la, l'ensemble forme un tout execute' randomly
// Le 1er thread s'executera toujous en 1er
	pthread_create(&identifiant_1, NULL, &sandbox_thread, NULL);		// Lui passer la fonction sandbox_thread ou un pointeur (&sandbox_thread) revient au meme
	pthread_create(&identifiant_2, NULL, &sandbox_thread, NULL);
	printf("%si is [%d]\n%s", GREEN, i, NC);
	printf("%si is [%d]\n%s", BLUE, i, NC);
	printf("%sIdentifiant_1 is [%li]\tIdentifiant_2 is [%li]\n%s", RED, identifiant_1, identifiant_2, NC);

	pthread_join(identifiant_1, NULL);
	printf("%si is [%d]\n%s", CYAN, i, NC);
	pthread_join(identifiant_2, NULL);
// The 2 threads have been joined (= they finished their execution), nothing else can happen from here
	printf("%si is [%d]\n%s", YELLOW, i, NC);

	return (0);
}
