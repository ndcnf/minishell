/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/29 10:37:46 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_var(t_data *dt, int in, int i)
{
	char	*tempura;
	int		j;

	tempura = ft_strchr(dt->in[in].elem->cont[i], '$');
	while (tempura)
	{
		tempura = ft_strtrim(dt->in[in].elem->cont[i], "$");
		j = where_in_env(dt, tempura, ft_strlen(tempura));
		if (j == NO_RESULT)
		{
			tempura = ft_strchr(dt->in[in].elem->cont[i] + ft_strlen(tempura), '$');
			continue;
		}
		free (dt->in[in].elem->cont[i]);
		dt->in[in].elem->cont[i] = ft_strdup(parse_env(dt->env[j])[1]);
		free (tempura);
		tempura = ft_strchr(dt->in[in].elem->cont[i], '$');
	}
}
