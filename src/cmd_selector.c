/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 15:39:15 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_selector(t_data *dt, int i)
{
	if (dt->n_cmd == 1)
	{
		dt->in[i].pid = NO_RESULT;
		if (builtins_selector(dt, i) == NO_RESULT)
			exec_boarders(dt, i);
	}
	else
		exec_boarders(dt, i);
}

int	builtins_selector(t_data *dt, int i)
{
	t_fd	fd_keeper;

	fd_keeper.out = dup(STDOUT_FILENO);
	fd_keeper.in = dup(STDIN_FILENO);
	if (ft_strncmp(dt->in[i].elem->cont[0], "echo", 5) == 0)
	{
		fprintf(stderr, "avant dup2 out [%d]\n", dt->in[i].fd.out);
		if (dt->in[i].fd.out > 2)
		{
			dup2(dt->in[i].fd.out, STDOUT_FILENO);
			close(dt->in[i].fd.out);
		}
		fprintf(stderr, "avant dup2 in [%d]\n", dt->in[i].fd.in);
		if (dt->in[i].fd.in > 2)
		{
			dup2(dt->in[i].fd.in, STDIN_FILENO);
			close(dt->in[i].fd.in);
		}
		b_echo(dt, i);
		dup2(fd_keeper.out, STDOUT_FILENO);
		dup2(fd_keeper.in, STDIN_FILENO);
		close(fd_keeper.out);
		close(fd_keeper.in);
	}
	else if (ft_strncmp(dt->in[i].elem->cont[0], "pwd", 4) == 0)
		b_pwd(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "cd", 3) == 0)
		b_cd(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "exit", 5) == 0)
		b_exit(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "env", 4) == 0)
		b_env(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "export", 7) == 0)
		b_export(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "unset", 6) == 0)
		b_unset(dt, i);
	else
		return (NO_RESULT);
	return (0);
}
