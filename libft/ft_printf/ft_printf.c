/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:05:40 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/18 10:45:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_args_check(const char args, va_list ap)
{
	int	compteur;

	compteur = 0;
	if (args == 'c')
		compteur += ft_print_char(va_arg(ap, int));
	else if (args == 's')
		compteur += ft_print_str(va_arg(ap, char *));
	else if (args == 'i' || args == 'd')
		compteur += ft_print_int(va_arg(ap, int));
	else if (args == 'p')
		compteur += ft_print_ptr(va_arg(ap, void *));
	else if (args == 'u')
		compteur += ft_print_unsigned_int(va_arg(ap, unsigned int));
	else if (args == 'X')
		compteur += ft_print_hexa(va_arg(ap, unsigned int), 1);
	else if (args == 'x')
		compteur += ft_print_hexa(va_arg(ap, unsigned int), 0);
	else if (args == '%')
		compteur += ft_print_char('%');
	return (compteur);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		compteur_total;

	i = 0;
	compteur_total = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i])
				compteur_total += ft_args_check(format[i], ap);
		}
		else
			compteur_total += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (compteur_total);
}
