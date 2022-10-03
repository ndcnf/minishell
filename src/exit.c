/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:13 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/03 14:53:09 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	the_end(char *msg, int status, int print)
{
	if (!msg)
		msg = ERROR;
	if (status || print)
		ft_printf(msg);
	g_exit_stat = status;
	return (status);
}

int	return_exit(t_data *dt, char *msg, int status, int print)
{
	// int	i;
	// int	j;

	// i = 0;
	// while (i < dt->n_cmd)
	// {
	// 	j = 0;
	// 	while (j < dt->in[i].n_elem)
	// 	{
	// 		free(dt->in[i].elem->cont[j]);
	// 		j++;
	// 	}
	// 	free(dt->in[i].elem);
	// 	i++;
	// }
	// free(dt->in);
	the_end(msg, status, print);
	(void)dt;
	return (g_exit_stat);
}
