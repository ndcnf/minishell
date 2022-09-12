/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:32:51 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/12 10:33:48 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	d_quotes_mgmt(t_input *input, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 0;
	j = i;
	while (s[i] && s[i] != '\"')
	{
		size++;
		i++;
	}
	i = j;
	input->elem->content[n] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != '\"')
		input->elem->content[n][k++] = s[i++];
	if (i == 1)
		input->elem->content[n][k] = ' ';
	return (i + 1);
}

int	s_quotes_mgmt(t_input *input, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 0;
	j = i;
	while (s[i] && s[i] != '\'')
	{
		size++;
		i++;
	}
	i = j;
	input->elem->content[n] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != '\'')
		input->elem->content[n][k++] = s[i++];
	if (i == 1)
		input->elem->content[n][k] = ' ';
	return (i + 1);
}

int	no_quote_mgmt(t_input *input, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 0;
	j = i;
	while (s[i] && s[i] != ' ')
	{
		size++;
		i++;
	}
	i = j;
	input->elem->content[n] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != ' ')
		input->elem->content[n][k++] = s[i++];
	return (i);
}
