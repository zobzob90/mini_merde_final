/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ctrl_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:50:17 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/13 13:58:50 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_cond(char *s1, char *s2, int to_free)
{
	if (to_free == FREE_S1 || to_free == FREE_ALL)
		free(s1);
	if (to_free == FREE_S2 || to_free == FREE_ALL)
		free(s2);
}

char	*ft_strjoin_ctr_free(char *s1, char *s2, int to_free)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new_str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free_cond(s1, s2, to_free);
	return (new_str);
}
