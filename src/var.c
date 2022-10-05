/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 10:10:43 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_quest(t_data *dt, int in, int i)
{
	if (dt->in[in].elem->cont[i][1] == '?')
	{
		free(dt->in[in].elem->cont[i]);
		dt->in[in].elem->cont[i] = ft_itoa(g_exit_stat);
	}
}

void	conv_var(t_data *dt, int in, int i)
{
	char	*tmp;
	char	**env_tmp;
	int		j;

	tmp = ft_strchr(dt->in[in].elem->cont[i], '$');
	while (tmp)
	{
		conv_quest(dt, in, i);
		tmp = ft_strtrim(dt->in[in].elem->cont[i], "$");
		j = where_in_env(dt, tmp, ft_strlen(tmp));
		if (j == NO_RESULT)
		{
			j = ft_strlen(tmp) + 1;
			free(tmp);
			tmp = ft_strchr(dt->in[in].elem->cont[i] + j, '$');
			continue ;
		}
		free (dt->in[in].elem->cont[i]);
		env_tmp = parse_env(dt->env[j]);
		dt->in[in].elem->cont[i] = ft_strdup(env_tmp[1]);
		freearray(env_tmp, 2);
		free (tmp);
		tmp = ft_strchr(dt->in[in].elem->cont[i], '$');
	}
}
