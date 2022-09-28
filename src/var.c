/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/28 11:06:23 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_var(t_data *dt, int in)
{
	int		i;
	char	*tempura;
	int		j;

	i = 0;
	while (i < dt->in[in].n_elem)
	{
		j = 0;
		tempura = ft_strchr(dt->in[in].elem->cont[i], '$');
		if (tempura)
		{
			tempura = ft_strtrim(dt->in[in].elem->cont[i], "$");
			j = where_in_env(dt, tempura, ft_strlen(tempura));
			free (dt->in[in].elem->cont[i]);
			if (j == NO_RESULT)
			{
				dt->in[in].elem->cont[i] = ft_strdup(" ");
				free (tempura);
				break ;
			}
			dt->in[in].elem->cont[i] = ft_strdup(parse_env(dt->env[j])[1]);
			free (tempura);
		}
		i++;
	}
}
