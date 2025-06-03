/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:12:07 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/19 14:12:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*scopy;

	i = 0;
	scopy = (unsigned char *)s;
	while (i < n)
	{
		scopy[i] = '\0';
		i++;
	}
}
