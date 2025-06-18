/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:37:16 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/03 11:54:13 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_str;

	if (!s1 || !s2)
	{
		printf("je suis une salope\n");
		return (NULL);
	}
	new_str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	printf("je sujis laaaa\n");
	if (!new_str)
	{
		printf("je suis un caca\n");
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	printf("[DEBUG STRJOIN] new_str= %s\n", new_str);
	return (new_str);
}
