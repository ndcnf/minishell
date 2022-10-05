/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:13 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 20:41:01 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	the_end(char *msg, int status, int print)
{
	if (!msg)
		msg = ERROR;
	if (status)
		ft_putstr_fd(msg, STDERR_FILENO);
	else if (print)
		ft_printf(msg);
	g_exit_stat = status;
	return (status);
}

int	msg_cmd_404(t_data *dt, int i)
{
	g_exit_stat = ERR_404;
	ft_printf("%s: command not found\n", dt->in[i].elem->cont[0]);
	return (g_exit_stat);
}
