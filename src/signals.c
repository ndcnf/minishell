/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:32:06 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 19:53:29 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_int(int c)
{
	if (c == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_termios(void)
{
	struct termios	rplc;

	tcgetattr(STDIN_FILENO, &rplc);
	rplc.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &rplc);
}

void	sig_double(int c)
{
	if (c == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (c == SIGQUIT)
	{
		write(1, "Quit : 3\n", 9);
		rl_on_new_line();
	}
}
