/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:42:48 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 17:52:03 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns a customized shell prompt string based
on the current 'drucker_mode' setting.*/

char	*get_prompt(t_shell *shell)
{
	char	*input;

	if (shell->drucker_mode == 1)
		input = readline
			("\001\033[1;32m\002minishell drucker 🎙️ ➤ \001\033[0m\002");
	else if (shell->drucker_mode == 2)
		input = readline
			("\001\033[1;32m\002jacquie et mini_michel ➤ \001\033[0m\002");
	else if (shell->drucker_mode == 3)
		input = readline
			("\001\033[1;31m\002mini_hell 🔥 ➤ \001\033[0m\002");
	else if (shell->drucker_mode == 4)
		input = readline
			("\001\033[1;32m\002mini_merde 💩 ➤ \001\033[0m\002");
	else if (shell->drucker_mode == 5)
		input = readline
			("\001\033[1;32m\002mini_moulinette 🐱‍💻 ➤ \001\033[0m\002");
	else if (shell->drucker_mode == 6)
		input = readline
			("\001\033[1;32m\002kevin_shell 🍆 ➤ \001\033[0m\002");
	else
		input = readline
			("\001\033[1;32m\002minishell ➤ \001\033[0m\002");
	return (input);
}
