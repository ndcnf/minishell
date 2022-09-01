/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:36:28 by marlene           #+#    #+#             */
/*   Updated: 2022/08/31 17:22:34 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(t_builtins *bs, char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] != ' ')
		{
			bs->len = ft_strlen(in) - i;
			return (1);
		}
		i++;
	}
	return (0);
}
