/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:32:06 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 11:47:29 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		write(1, "Quit : 3\n", 9);
		rl_on_new_line();
	}
}
