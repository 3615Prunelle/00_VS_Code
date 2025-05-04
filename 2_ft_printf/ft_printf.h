/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/29 19:09:24 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

# include "../1_Libft/libft.h"

//All the #define can also be placed here
# define HEXA_MIN "0123456789abcdef"
# define HEXA_MAJ "0123456789ABCDEF"

// Main Function
int				ft_printf(const char *string, ...);

// Helpers
//char			*ft_itoa(int n);
int				specifiers_call(char c, va_list ptr_string);
int				c_specifier(char c);
int				s_specifier(char *c);
int				d_and_i_specifier(int i);
unsigned int	u_specifier(unsigned int i);
int				p_specifier(void *p);
int				x_specifier(unsigned long long i, char *hexa);
//size_t			ft_strlen(const char *str);

#endif
