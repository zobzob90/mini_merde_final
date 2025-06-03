/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:19:51 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 15:42:46 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_print_hexa(unsigned long nb, int is_uppercase)
{
	char				*lowercase_hexa;
	char				*uppercase_hexa;
	unsigned int		compteur;

	compteur = 0;
	lowercase_hexa = "0123456789abcdef";
	uppercase_hexa = "0123456789ABCDEF";
	if (nb >= 16)
		compteur += ft_print_hexa(nb / 16, is_uppercase);
	if (is_uppercase)
		compteur += ft_print_char(uppercase_hexa[nb % 16]);
	else
		compteur += ft_print_char(lowercase_hexa[nb % 16]);
	return (compteur);
}
