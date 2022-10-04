/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/04 16:15:55 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_boarders(t_data *dt, int in)
{
	int			i;
	int			status;
	int			ok;

	ok = 0;
	i = where_in_env(dt, "PATH", 4);
	if (i == NO_RESULT)
	{
		the_end(CMD_404, EXIT_FAILURE, 1);
		return ;
	}
	ok = exec_middle(dt, in, ok, i);
	if (ok == 0)
		the_end(CMD_404, EXIT_FAILURE, 1);
	while (in < dt->n_cmd)
		waitpid(dt->in[in++].pid, &status, 0);
}

int	exec_middle(t_data *dt, int in, int ok, int i)
{
	char		**tdpp;
	char		**tmp;
	char		*cmd_path;
	struct stat	buff;

	tmp = parse_env(dt->env[i]);
	tdpp = ft_split(tmp[1], ':');
	freearray(tmp, 2);
	i = 0;
	while (tdpp[i])
	{
		cmd_path = ft_strjoin_free(tdpp[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, dt->in[in].elem->cont[0]);
		if (!stat(cmd_path, &buff))
		{
			ok = 1;
			dt->in[in].pid = fork();
			if (dt->in[in].pid == 0)
			{
				execve(cmd_path, dt->in[in].elem->cont, dt->env);
			}
		}
		i++;
		free(cmd_path);
	}
	free(tdpp);
	return (ok);
}
