/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 11:14:24 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	t_data	dt;
	int		i;
	int		j;
	int		quote;

	g_exit_stat = 0;
	b_init(&dt, envp);
	while (1)
	{
		if (termios_line(&dt) == 1)
			continue ;
		i = 0;
		while (i < dt.n_cmd)
		{
			j = 0;
			init_redir(&dt, i);
			while (j < dt.in[i].n_elem)
			{
				trimquotes(&dt, "\"", i, j);
				quote = trimquotes(&dt, "\'", i, j);
				if (!quote)
					conv_var(&dt, i, j);
				if (checker_redir(&dt, i, j) == NO_RESULT)
					break ;
				if (dt.in[i].n_redir > 0)
					j--;
				j++;
			}
			if (dt.in[i].pos_red == NO_RESULT)
				break ;
			// UNIQUEMENT POUR TESTS //////////////////////////////////////////////////
			// j = 0;
			// ft_printf("n_elem [%d]\n", dt.in[i].n_elem);
			// while (j < dt.in[i].n_elem)
			// {
			// 	ft_printf("new_elem[%d][%d] : [%s]\n", i, j, dt.in[i].elem->cont[j]);
			// 	j++;
			// }
			// int z = 0;
			// while (z < dt.in[i].n_redir)
			// {
			// 	ft_printf("redir [%s] : [%s]\n", dt.in[i].red[z].chevron, dt.in[i].red[z].file);
			// 	z++;
			// }
			///////////////////////////////////////////////////////////////////////////
			i++;
		}
		i = 0;
		exec_redir(&dt);
		while (i < dt.n_cmd)
		{
			cmd_selector(&dt, i);
			i++;
		}
		i = 0;
		while (i < dt.n_cmd)
		{
			ft_printf("avant [%d]\n", g_exit_stat);
			waitpid(dt.in[i++].pid, &g_exit_stat, 0);
			ft_printf("pendant [%d]\n", g_exit_stat);
			if (WIFSIGNALED(g_exit_stat))
				g_exit_stat = ERR_SIGN + g_exit_stat;
			if (WIFEXITED(g_exit_stat))
				g_exit_stat = WEXITSTATUS(g_exit_stat);
			ft_printf("apres [%d]\n", g_exit_stat);
		}
		free_data(&dt);
		// POUR TESTS UNIQUEMENT //////////////////////////////////////////////
		//ft_printf("globale maintenant = %d\n", g_exit_stat);
		///////////////////////////////////////////////////////////////////////
	}
	free(dt.path);
}

int	termios_line(t_data *dt)
{
	char			*prompt;
	struct termios	rplc;
	struct termios	saved;

	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &rplc);
	rplc.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rplc);
	prompt = readline("\e[36mmarynad$ \e[0m");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	if (!prompt)
		exit(the_end("exit\n", EXIT_SUCCESS, 1));
	if (!prompt[0] || parsing_init(prompt, dt) == NO_RESULT)
	{
		free(prompt);
		return (1);
	}
	add_history(prompt);
	free(prompt);
	return (0);
}
