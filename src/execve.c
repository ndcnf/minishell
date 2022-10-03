/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/03 17:41:39 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *dt, int in)
{
	char		*cmd_path;
	char		**tdpp;
	struct stat	buff;
	int			i;
	int			j;
	int			status;
	int			ok;

	j = -1;
	i = where_in_env(dt, "PATH", 4);
	if (i == NO_RESULT)
	{
		the_end(CMD_404, EXIT_FAILURE, 1);
		return ;
	}
	tdpp = ft_split((parse_env(dt->env[i])[1]), ':');
	i = 0;
	ok = 0;
	while (tdpp[i])
	{
		cmd_path = ft_strjoin(tdpp[i], "/");
		cmd_path = ft_strjoin(cmd_path, dt->in[in].elem->cont[0]);
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
	}
	if (ok == 0)
			the_end(CMD_404, EXIT_FAILURE, 1);
	while (dt->in[in].cont != NULL)
		waitpid(dt->in[in++].pid, &status, 0);
}
