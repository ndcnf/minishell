/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:36:28 by marlene           #+#    #+#             */
/*   Updated: 2022/10/05 14:19:44 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_input *in, char *s)
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
	in->n_elem += (s_quotes + d_quotes);
	return (0);
}

int	skip_spaces(char *s, int i)
{
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		return (i);
	}
	return (i);
}

int	skip_quotes(t_input *in, int i)
{
	while (i < in->n_elem)
	{
		if (ft_strncmp(in->elem->cont[i], "\"", 1) == 0)
			i++;
		else if (ft_strncmp(in->elem->cont[i], "\'", 1) == 0)
			i++;
		else
			return (i);
	}
	return (i);
}

int	skip_n(t_input *in, int i)
{
	while (i < in->n_elem)
	{
		if (ft_strncmp(in->elem->cont[i], "-n", 1) == 0)
			i++;
		else
			return (i);
	}
	return (i);
}

void	space_counter(t_input *in, char *s)
{
	int	i;

	i = 0;
	i = skip_spaces(s, i);
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		else if (s[i] == ' ' && s[i + 1] == '\0')
			break ;
		else if (s[i] == ' ' && s[i + 1] != ' ')
			in->n_elem++;
		i++;
	}
}
