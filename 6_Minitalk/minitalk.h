/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:41:59 by sophie            #+#    #+#             */
/*   Updated: 2025/08/18 11:53:18 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// ⚪ #define


// ⚪ #include
// #define _POSIX_C_SOURCE 200809L	// Décommenter si 42 VS Code ne reconnait pas certaines variables/fonctions
									// comme sigset_t ou sigaction. Autre option : activer _POSIX_C_SOURCE dans set up VSCode :
									// Menu View → Command Palette
									// Taper : C/C++: Edit Configurations (UI)
									// Aller dans la section "Defines"
									// Copier coller cette ligne : _POSIX_C_SOURCE=200809L
									// Redémarrer VSCode
#include <signal.h>
#include <errno.h>	// Only for testing purposes (to see signal function error message if fails)
#include <string.h>	// Only for testing purposes (to see signal function error message if fails)
#include <unistd.h>	// Pour getpid, usleep (& others TBD)
#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ⚪ Include from other projects
// ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" dans tasks.json ou makefile
#include <libft.h>
#include <ft_printf.h>

// NOTE : mettre les dossiers 99 + 98 au lieu de ca ^ car ce projet dépend des .h + .a mais pas besoin du reste

// ⚪ Structs

// ⚪ Functions signatures - Part 1
unsigned char	*string_to_bit(char *s);						// Encryption
void 			print_char_from_8bits(unsigned char *bin_array);		// Decryption
void			send_newline_binary(int server_PID);

// ⚪ Functions signatures - Part 2
void			send_signal(int signum);
void			got_signal(int signum);	// Est-ce nécessaire de mettre une signature de handler ici ?

// ⚪ Clean up functions

// ⚪ Test functions

#endif
