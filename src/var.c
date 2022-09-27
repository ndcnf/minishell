/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:34:51 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/27 14:52:46 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	conv_var(t_data *dt, int in)
{
	int		i;
	int		j;
	char	*exist_key;
	char	*tempura;

	i = 0;
	while (i < dt->in[in].n_elem)
	{
		j = 0;
		while (j < (int)ft_strlen(dt->in[in].elem->cont[i]))
		{
			tempura = ft_strchr(dt->in[in].elem->cont[i], '$');
			ft_printf("TEMPURA !!!!! [%s]\n", tempura);
			if (tempura)
			{
				exist_key = parse_env(dt->env[i])[0];
				ft_printf("J'ai vu un dollar, je m'en occupe.\n");
				// j++;
				// while (dt->in[in].elem->cont[i][j] != '$')
				// {

				// }

			}
			j++;
		}
		i++;
	}
}
