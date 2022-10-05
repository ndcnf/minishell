/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:13 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 13:28:19 by nchennaf         ###   ########.fr       */
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
