/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:13:54 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/19 14:14:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int character)
{
	if (character >= 'a' && character <= 'z')
		return (1);
	if (character >= 'A' && character <= 'Z')
		return (1);
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}
