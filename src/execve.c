/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 14:58:47 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *dt, int in)
{
	char		*cmd_path;
	char		**tdpp;
	struct stat	buff;
	int			i;

	i = 0;
	tdpp = ft_split(dt->path, ':');
	while (tdpp[i])
	{
		cmd_path = ft_strjoin(tdpp[i], "/");
		cmd_path = ft_strjoin(cmd_path, dt->in[in].elem->cont[0]);
		if (!stat(cmd_path, &buff))
		{
			if (execve(cmd_path, dt->in[in].elem->cont, dt->env) == -1)
				exit (1);
		}
		i++;
	}
	cmd_path = ft_strjoin("/usr/local/bin/", dt->in[in].elem->cont[0]); // ------ ne devrait pas etre ajoute. Le programme doit ne pas trouver lors d'ún unset du PATHpar exemple
}
