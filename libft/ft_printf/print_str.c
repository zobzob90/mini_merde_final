/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:43:27 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 12:01:29 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	i;
	int	compteur;

	i = 0;
	compteur = 0;
	if (str == NULL)
		compteur += ft_print_str("(null)");
	else
	{
		while (str[i])
		{
			compteur += ft_print_char(str[i]);
			i++;
		}
	}
	return (compteur);
}
