/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:36:40 by ertrigna          #+#    #+#             */
/*   Updated: 2025/02/28 11:16:43 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_join(char *s1, char *s2, int sizeS1, int sizeS2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	result = malloc(sizeof(char) * (sizeS1 + sizeS2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < sizeS1)
	{
		result[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (j < sizeS2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
