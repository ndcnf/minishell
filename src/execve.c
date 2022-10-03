/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/03 14:53:46 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_data *dt, int in)
{
	char		*cmd_path;
	char		**tdpp;
	struct stat	buff;
	int			i;
	int			j;
	int			status;

	i = 0;
	j = -1;
	/* le path doit etre recupere depuis le env des builtins.
	Il faudra utiliser 'where_in_env' plutot ici pour les cas de suppression (unset)
	du PATH lors de l'eval
	Il ne faudra pas utiliser dt->path. La maniere de faire est juste,
	mais la variable utilisee ici est fausse */
	tdpp = ft_split(dt->path, ':');
	while (tdpp[i])
	{
		cmd_path = ft_strjoin(tdpp[i], "/");
		cmd_path = ft_strjoin(cmd_path, dt->in[in].elem->cont[0]);
		if (!stat(cmd_path, &buff))
		{
			dt->in[in].pid = fork();
			if (dt->in[in].pid == 0)
			{
				execve(cmd_path, dt->in[in].elem->cont, dt->env);
				return (0);
			}
		}
		i++;
	}
	while (dt->in[in].cont != NULL)
		waitpid(dt->in[in++].pid, &status, 0);
	return (-1);
}
