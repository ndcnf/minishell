/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:13 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 11:10:10 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	the_end(char *msg, int status)
{
	if (!msg)
		msg = "error\n";
	if (status)
		ft_printf(msg);
	g_exit_stat = status;
	return (status);
}
