/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:54:01 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 11:53:30 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_data(t_data *dt)
{
	int	i;
	int	j;

	i = 0;
	while (i < dt->n_cmd)
	{
		j = 0;
		while (j < dt->in[i].n_elem)
			free(dt->in[i].elem->cont[j++]);
		free_redir(dt, i);
		free(dt->in[i].elem->cont);
		free(dt->in[i].elem);
		i++;
	}
	free(dt->in);
}

void	free_redir(t_data *dt, int i)
{
	int	j;

	j = 0;
	while (j < dt->in[i].n_redir)
	{
		free(dt->in[i].red[j].chevron);
		free(dt->in[i].red[j].file);
		j++;
	}
	free(dt->in[i].red);
}
