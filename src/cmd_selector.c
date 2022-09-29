/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 15:14:02 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_selector(t_data *dt, int i)
{
	if (dt->n_cmd == 0) // cette condition devra etre faite au debut meme du programme, pas ici
		printf("\n");
	if (ft_strncmp(dt->in[i].elem->cont[0], "echo", 5) == 0)
		b_echo(dt, i);
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

	// freearray(bs.env, bs.n_env);
	// freearray(bs.args, bs.n_args);
}