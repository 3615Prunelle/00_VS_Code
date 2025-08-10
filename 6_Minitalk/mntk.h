/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mntk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:41:59 by sophie            #+#    #+#             */
/*   Updated: 2025/08/10 18:06:47 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// ⚪ #define


// ⚪ #include
#include <signal.h>
#include <errno.h>	// Only for testing purposes (to see signal function error message if fails)
#include <string.h>	// Only for testing purposes (to see signal function error message if fails)
#include <unistd.h>	// Pour getpid, usleep (& others TBD)

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json ou makefile
#include <libft.h>
#include <ft_printf.h>

// NOTE : mettre les dossiers 99 + 98 au lieu de ca ^ car ce projet dépend des .h + .a mais pas besoin du reste

// ⚪ Structs

// ⚪ Functions signatures - Part 1

// ⚪ Functions signatures - Part 2

// ⚪ Clean up functions

// ⚪ Test functions

#endif
