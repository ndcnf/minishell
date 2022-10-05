/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:32:06 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 19:56:23 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_set_signal(void)
{
	struct termios	rplc;
	struct termios	saved;
	char			*prompt;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int);
	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &rplc);
	rplc.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rplc);
	prompt = readline("\e[36mmarynad$ \e[0m");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	return (prompt);
}

void	sig_int(int c)
{
	if (c == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_double(int c)
{
	if (c == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (c == SIGQUIT)
	{
		ft_printf("Quit : %d\n", c);
		rl_on_new_line();
	}
}
