/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:47:30 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 17:47:40 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Implements the built-in 'env' command by printing
the current environment variables.*/

int	get_env_built(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}
