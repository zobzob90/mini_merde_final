/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:26:16 by ertrigna          #+#    #+#             */
/*   Updated: 2025/02/28 11:16:30 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include "../libft.h"

/*utils*/
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_str_join(char *s1, char *s2, int sizeS1, int sizeS2);

/*GNL*/
char	*get_next_line(int fd);

#endif