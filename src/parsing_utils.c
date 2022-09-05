/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:36:28 by marlene           #+#    #+#             */
/*   Updated: 2022/09/05 14:46:13 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *s)
{
	int	nb_quotes;
	int	i;

	nb_quotes = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			nb_quotes++;
		i++;
	}
	if (nb_quotes % 2)
		return (1);
	i = 0;
	nb_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			nb_quotes++;
		i++;
	}
	if (nb_quotes % 2)
		return (1);
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
