/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/04 17:57:02 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_selector(t_data *dt, int i)
{
	if (builtins_selector(dt, i) == NO_RESULT)
		exec_boarders(dt, i);
}

int	builtins_selector(t_data *dt, int i)
{
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
	else
		return (NO_RESULT);
	return (0);
}
