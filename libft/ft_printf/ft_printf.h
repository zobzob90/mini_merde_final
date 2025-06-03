/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:32:28 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 15:43:08 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>

/*Basic Function*/

/*For %u*/
unsigned int	ft_print_unsigned_int(unsigned int nb);

/*For %x or %X*/
unsigned int	ft_print_hexa(unsigned long nb, int is_uppercase);

/*For %s or %c*/
int				ft_print_char(char c);
int				ft_print_str(char *str);

/*For %d or %i*/
int				ft_print_int(int nb);

/*For %p*/
int				ft_print_ptr(void *ptr);

/*Mandatory Function*/
int				ft_args_check(const char args, va_list ap);
int				ft_printf(const char *format, ...);

#endif