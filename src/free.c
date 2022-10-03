/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:54:01 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/03 18:25:31 by nchennaf         ###   ########.fr       */
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
		{
			free(dt->in[i].elem->cont[j]);
			j++;
		}
		j = 0;
		// if (dt->in[i].pos_red != NO_RESULT)
		// {
			while (j < dt->in[i].n_redir)
			{
				printf("n_redir%d\n", dt->in[i].n_redir);
				free(dt->in[i].red[j].chevron);
				// if (dt->in[i].pos_red != NO_RESULT)
				free(dt->in[i].red[j].file);
				j++;
			}
			// if (dt->in[i].n_redir)
			free(dt->in[i].red);
		// }
		free(dt->in[i].elem->cont);
		free(dt->in[i].elem);
		i++;
	}
	free(dt->in);
}
