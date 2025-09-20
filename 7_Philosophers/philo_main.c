/* Notes random
🔴 Philosophers = Processes (NB : Processes are composed of one or multiple threads, and treads are composed of instructions). But NB : One thread = one process
🟠 Chopsticks = Ressources that have to be shared between processes (but one at a time)
🟡 Your program(s) must take the following arguments:
			◦ number_of_philosophers: The number of philosophers and also the number of chopsticks.
			◦ time_to_die (in milliseconds): If a philosopher has not started eating within time_to_die milliseconds since
						the start of their last meal or the start of the simulation, they die.
			◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
						During that time, they will need to hold two chopsticks.
			◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
			◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers
						have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops.
						If not specified, the simulation stops when a philosopher dies.
🟢 Study pthread_mutex_lock & pthread_mutex_unlock
🔵 pthread_join = equivalent of 'wait'
🟣 Les threads ne sont pas hiérarchisés. Pas de concept de parent/child comme pour les processes
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

# include "philosophers.h"

void	*chopsticks_party(void *arg)
{
	// int	*amount_of_chopsticks = arg;
	struct all_data *bon_appetit = arg;


}

int	main(int argc, char **argv)
{
	int		amount_of_yakuzas = atoi(argv[1]);								// Fonction pas autorisee, c/c celle de ma libft later
	bool	*chopsticks;
	int		time_to_die = atoi(argv[2]);									// In milliseconds - Is it the right kind of variable ?
	int		time_to_eat = atoi(argv[3]);									// Same question as above
	int		time_to_sleep= atoi(argv[4]);									// Same question as above
	int		number_of_times_each_philosopher_must_eat= atoi(argv[5]);		// Optional argument
	int 	i = 0;

	pthread_t	*all_yakuzas;	// Array of phtreads
	all_yakuzas = malloc(sizeof(pthread_t) * amount_of_yakuzas);
	chopsticks = malloc(sizeof(bool) * amount_of_yakuzas);

	// pick one or merge or none ?
	all_data	bon_appetit = {all_yakuzas, amount_of_yakuzas, &chopsticks, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosopher_must_eat};
	one_bro	that_one = {1, EATING, true, true};


/*		NEXT :
	- Declarer les etats : eating, thinking, and sleeping (sous forme de define ? bool ?) - Attention, global variables are forbidden, donc seulement les valeurs immuables
	- Struct pour chaque yakuza : position / current state / check chopstick right / check chopstick left (?)
	- Declarer les chopsticks (sous forme de bool ?), meme quantite que les philo
	- Delarer le plat de ramen (or maybe not ?)
	- Mettre en place les mutex
*/
	while (i < amount_of_yakuzas)
	{
		chopsticks[i] = AVAILABLE;
		pthread_create(&all_yakuzas[i], NULL, chopsticks_party, &bon_appetit);
		i++;
	}

	// garder a fin ?
	i = 0;
	while (i < amount_of_yakuzas)
	{
		pthread_join(&all_yakuzas[i], NULL);
		i++;
	}
	return(0);
}
