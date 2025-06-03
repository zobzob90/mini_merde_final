/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:51:55 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 14:44:36 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_print_unsigned_int(unsigned int nb)
{
	unsigned int	compteur;

	compteur = 0;
	if (nb >= 10)
		compteur += ft_print_unsigned_int(nb / 10);
	compteur += ft_print_char((nb % 10) + 48);
	return (compteur);
}
