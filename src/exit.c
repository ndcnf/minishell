/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:13 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/01 12:05:17 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	the_end(char *msg, int status)
{
	if (!msg)
		msg = ERROR;
	if (status)
		ft_printf(msg);
	g_exit_stat = status;
	return (status);
}

int	return_exit()
{
	the_end(CMD_404, g_exit_stat);
	return (g_exit_stat);
}
