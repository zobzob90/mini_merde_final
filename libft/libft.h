/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:16:21 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/13 14:03:22 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

# define FREE_NONE 0
# define FREE_S1 1
# define FREE_S2 2
# define FREE_ALL 3

/*ascii to int or long int*/
long int	ft_atol(const char *str);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
/*split*/
char		**ft_split(char const *s, char c);
/*compare*/
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
/*free_tab*/
void		ft_free_tab(char **tab);
/*str dup concat or copy*/
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, size_t n);
char		*ft_strjoin(char *s1, const char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_ctr_free(char *s1, char *s2, int to_free);
char		*ft_strcat(char *dest, char *src);
size_t		ft_strspn(const char *s, const char *accept);
/*print c or str*/
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
/*sub*/
char		*ft_substr(char const *s, unsigned int start, size_t len);
/*alloc memory*/
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
/*is_function*/
int			ft_isalnum(int character);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
/*size function*/
size_t		ft_strlen(const char *s);
#endif