/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 16:24:41 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_var(t_data *dt, int in, int i)
{
	char	*tmp;
	int		j;

	tmp = ft_strchr(dt->in[in].elem->cont[i], '$');
	while (tmp)
	{
		tmp = ft_strtrim(dt->in[in].elem->cont[i], "$");
		j = where_in_env(dt, tmp, ft_strlen(tmp));
		if (j == NO_RESULT)
		{
			tmp = ft_strchr(dt->in[in].elem->cont[i] + ft_strlen(tmp), '$');
			continue ;
		}
		free (dt->in[in].elem->cont[i]);
		dt->in[in].elem->cont[i] = ft_strdup(parse_env(dt->env[j])[1]);
		free (tmp);
		tmp = ft_strchr(dt->in[in].elem->cont[i], '$');
	}
}
