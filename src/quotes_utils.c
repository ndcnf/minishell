/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:29:31 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 16:24:10 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	trimquotes(t_data *dt, char *s, int in, int i)
{
	char	*tempura;
	int		ret;

	ret = 0;
	if (ft_strncmp(dt->in[in].elem->cont[i], s, ft_strlen(s)) == 0)
	{
		tempura = dt->in[in].elem->cont[i];
		dt->in[in].elem->cont[i] = ft_strtrim(dt->in[in].elem->cont[i], s);
		free(tempura);
		ret = 1;
	}
	return (ret);
}
