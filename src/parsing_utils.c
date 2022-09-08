/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:36:28 by marlene           #+#    #+#             */
/*   Updated: 2022/09/07 13:21:33 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_input *input, char *s)
{
	int	s_quotes;
	int	d_quotes;
	int	i;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s_quotes++;
		if (s[i] == '\"')
			d_quotes++;
		i++;
	}
	if (s_quotes % 2 || d_quotes % 2)
		return (1);
	input->nb_elem += (s_quotes + d_quotes);
	return (0);
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		return (i);
	}
	return (i);
}

void	space_counter(t_input *input, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] != ' ')
			input->nb_elem++;
		i++;
	}
}
