/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/27 21:14:01 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_var(t_data *dt, int in)
{
	int		i;
	char	*exist_key;
	char	*tempura;
	int		len;
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
			exist_key = parse_env(dt->env[j])[0];
			len = ft_strlen(parse_env(dt->env[j])[1]);
			free (dt->in[in].elem->cont[i]);
			dt->in[in].elem->cont[i] = ft_strdup(parse_env(dt->env[j])[1]);
			free (tempura);
		}
		i++;
	}
}
