/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:21:24 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 15:41:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(void *ptr)
{
	int	compteur;

	compteur = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	compteur += ft_print_char('0');
	compteur += ft_print_char('x');
	compteur += ft_print_hexa((unsigned long)ptr, 0);
	return (compteur);
}
