/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:51:00 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/18 10:34:53 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int nb)
{
	int	compteur;

	compteur = 0;
	if (nb == -2147483648)
	{
		compteur += write(1, "-2147483648", 11);
		return (compteur);
	}
	if (nb < 0)
	{
		compteur += ft_print_char('-');
		nb = -nb;
	}
	if (nb >= 10)
		compteur += ft_print_int(nb / 10);
	compteur += ft_print_char((nb % 10) + '0');
	return (compteur);
}
