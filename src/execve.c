/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 19:38:44 by mthiesso         ###   ########.fr       */
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
