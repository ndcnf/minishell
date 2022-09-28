/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elem_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:08:20 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 18:48:20 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nb_cmd(t_data *dt, char *args, int i)
{
	while (args[i])
	{
		if (args[i] == '\"' || args[i] == '\'')
			i = is_quotes(args, i);
		if (args[i] == '|')
			dt->n_cmd++;
		i++;
	}
}

int	malloc_elem(t_input *in, char *s, int i, int n)
{
	int	j;

	j = 0;
	if (s[i] == '\"' || s[i] == '\'')
			j = (is_quotes(s, i) + 1);
	else
	{
		while (s[i])
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				j = (is_quotes(s, i) + 1);
				i = j;
			}
			if (!s[i])
				break ;
			if (s[i] == ' ')
				break ;
			i++;
			j++;
		}
	}
	in->elem->cont[n] = malloc(sizeof(char) * j + 1);
	return (j);
}

int	into_elem_quotes(t_input *in, char *s, int i, int n)
{
	if (s[i] == '\"' || s[i] == '\'')
	{
		in->elem->cont[n][i] = s[i];
		i++;
		while (s[i] != '\"' && s[i] != '\'')
		{
			in->elem->cont[n][i] = s[i];
			i++;
		}
	}
	return (i);
}
