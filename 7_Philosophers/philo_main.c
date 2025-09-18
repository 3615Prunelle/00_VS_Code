/* Notes random
🔴 Philosophers = Processes (NB : Processes can contain multiple threads, and vice versa)
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
🟣
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

int	main(int argc, char **argv)
{
	int	number_of_philosophers = atoi(argv[1]);							// Fonction pas autorisee, c/c celle de ma libft later
	int	time_to_die = atoi(argv[2]);									// In milliseconds - Is it the right kind of variable ?
	int	time_to_eat = atoi(argv[3]);									// Same question as above
	int	time_to_sleep= atoi(argv[4]);									// Same question as above
	int	number_of_times_each_philosopher_must_eat= atoi(argv[5]);		// Optional argument

	return(0);
}
