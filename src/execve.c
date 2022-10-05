/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 19:48:51 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_boarders(t_data *dt, int in)
{
	int			i;
	int			ok;

	ok = 0;
	signal(SIGINT, sig_double);
	signal(SIGQUIT, sig_double);
	dt->in[in].pid = fork();
	if (dt->in[in].pid == 0)
	{
		if (builtins_selector(dt, in) == NO_RESULT)
		{
			if (on_my_way(dt, ok, dt->in[in].elem->cont[0], in) != 1)
			{
				i = where_in_env(dt, "PATH", 4);
				execution(dt, in, i, ok);
			}
		}
		exit (g_exit_stat);
	}
}

int	exec_middle(t_data *dt, int in, int ok, int i)
{
	char		**tdpp;
	char		**tmp;
	char		*cmd_path;

	tmp = parse_env(dt->env[i]);
	tdpp = ft_split(tmp[1], ':');
	freearray(tmp, 2);
	i = 0;
	while (tdpp[i])
	{
		cmd_path = ft_strjoin_free(tdpp[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, dt->in[in].elem->cont[0]);
		ok = on_my_way(dt, ok, cmd_path, in);
		i++;
		free(cmd_path);
	}
	free(tdpp);
	return (ok);
}

int	on_my_way(t_data *dt, int ok, char *cmd_path, int in)
{
	if (!access(cmd_path, X_OK))
	{
		if (dt->in[in].fd.out > 2)
			dup2(dt->in[in].fd.out, STDOUT_FILENO);
		if (dt->in[in].fd.in > 2)
			dup2(dt->in[in].fd.in, STDIN_FILENO);
		the_closer(dt);
		execve(cmd_path, dt->in[in].elem->cont, dt->env);
		exit (the_end(ERR_EXE, EXIT_FAILURE, 1));
	}
	return (ok);
}

void	execution(t_data *dt, int in, int i, int ok)
{
	if (i == NO_RESULT)
		the_end(CMD_404, ERR_404, 1);
	else
	{
		ok = exec_middle(dt, in, ok, i);
		if (ok == 0)
			the_end(CMD_404, ERR_404, 1);
	}
}
