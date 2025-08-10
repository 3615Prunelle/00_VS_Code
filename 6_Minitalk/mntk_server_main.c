/* Notes random
🔴 (client) String >> ASCII >> Binary >> Signals to Server >> Binary >> ASCII > String
🟠 8 bits per char * amount of chars = Amount of signals sent
🟡 Client has to encrypt (to binary) / Server has to decrypt (from binary)
🟢 PID = Process ID, qui reste le même pendant toute sa durée de vie
🟢 PPID = Parent Process ID
🔵 commande kill = envoyer un signal VS. Signal 9 KILL = Terminer un processus
🟣 Par ex : La commande kill permet d'envoyer le signal KILL
🟤 Exemple de commande pour liste des signaux : skill -L
⚫ SIGUSR = User defined signal (= custom = not defined by operating system)
⚫ ‼️ SIGUSR1 SIGUSR2 sont les seuls types de signaux autorisés dans ce projet
⚫ ‼️Il ne peut exister qu'un seul signal pendant d'un type donné.
		S'il arrive un autre signal du même type, il est perdu
⚪ TTY = Terminal d'où a été créé le processus
🔴 Etapes dans le processus :
	R Run (En cours)
	I Idle (bloqué/en attente depuis moins de 20 secondes)
	S Sleep (bloqué/en attente depuis +20s)
	T Arrêté
	Z Zombie Arrêté mais le parent (PPID) n'a pas encore connaissance
🟠 Un signal est logiciel (s'adresse à un processus)
   Une interruption est matérielle (s'adresse à un processeur)
Quoi fait quoi ?
◦ signal		sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the address of a programmer-defined function (a "signal handler").
◦ sigemptyset	initializes the signal set given by set to empty, with all signals excluded from the set.
◦ sigaddset		add signal signum from set.
◦ sigaction		change the action taken by a process on receipt of a specific signal.
◦ kill			send any signal to any process group or process.
       If pid is positive, then signal sig is sent to the process with the ID specified by pid.
       If pid equals 0, then sig is sent to every process in the process group of the calling process.
       If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below.
       If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.
◦ getpid	returns the process ID (PID) of the calling process.
◦ malloc
◦ free
◦ pause		causes the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function.
◦ sleep		Pause for NUMBER seconds. SUFFIX may be 's' for seconds (the default), 'm' for minutes, 'h' for hours or 'd' for days. NUMBER need not be an integer. Given two or more arguments, pause for the amount of time specified by the sum of their values.
◦ usleep	suspends execution of the calling thread for (at least) usec microseconds. The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.
◦ exit

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

#include "mntk.h"

int	main(void)
{
	// Server expect a signal from client
	int	process_id;

	// USR1 = 10	USR2 = 12

	ft_printf("About to receive a signal from client - PID [%i]\n", process_id);

	signal();

	ft_printf("Error ? : [%s]", strerror(errno));

	__sighandler_t

	return(0);
}
