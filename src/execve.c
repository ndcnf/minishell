/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/01 14:25:08 by nchennaf         ###   ########.fr       */
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
			execve(cmd_path, dt->in[in].elem->cont, dt->env);
		i++;
	}
}
