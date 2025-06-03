/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:11:27 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/08 11:48:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str2;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (len == 0)
		return (ft_strdup(""));
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		str2[i] = s[start + i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
