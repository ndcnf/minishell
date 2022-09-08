/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/08 13:58:13 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_init(char *args, t_input *input)
{
	int			i;

	i = 0;
	input = malloc(sizeof(t_input));
	input->elem = malloc(sizeof(t_elem));
	input->nb_cmd = 1;
	while (args[i])
	{
		if (args[i] == '|')
			input->nb_cmd++;
		i++;
	}
	input->content = ft_split(args, '|');
	i = 0;
	while (i < input->nb_cmd)
	{
		input->nb_elem = 1;
		input->content[i] = parse_cmd(input, input->content[i]);
		space_counter(input, input->content[i]);
		input->elem->content = malloc(sizeof(char *) * input->nb_elem);
		parsing_elem(input, input->content[i]);
		i++;
	}
}

char	*parse_cmd(t_input *input, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_quotes(input, s) == 1)
		printf("DEGAGE\n");
	s = ft_strtrim(s, " ");
	return (s);
}

void	parsing_elem(t_input *input, char *s)
{
	int	i;

	i = 0;
	if (s[0])
	{
		first_elem(input, s, s[0]);
	}
	ft_printf("elem 0 : [%s]\n", input->elem->content[0]);
	ft_printf("elem 1 : [%s]\n", input->elem->content[1]);
	ft_printf("elem 2 : [%s]\n", input->elem->content[2]);
}

void	first_elem(t_input *input, char *s, char c)
{
	int	i;

	i = 0;
	if (c == '\"')
	{
		input->elem->content[0] = ft_strdup("\"");
		i = d_quotes_mgmt(input, s, 1);
		input->elem->content[2] = ft_strdup("\"");
	}
	else if (c == '\'')
	{
		input->elem->content[0] = ft_strdup("\'");
		i = s_quotes_mgmt(input, s, 1);
		input->elem->content[2] = ft_strdup("\'");
	}
	else
	{
		input->elem->content[0] = ft_strdup("X");
		i = no_quote_mgmt(input, s, 0);
		input->elem->content[2] = ft_strdup("X");
	}
}

int	d_quotes_mgmt(t_input *input, char *s, int i)
{
	int		k;
	int		size;

	k = 0;
	size = 0;
	while (s[i] && s[i] != '\"')
	{
		size++;
		i++;
	}
	i = 1;
	input->elem->content[1] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != '\"')
		input->elem->content[1][k++] = s[i++];
	if (i == 1)
		input->elem->content[1][k] = ' ';
	return (i);
}

int	s_quotes_mgmt(t_input *input, char *s, int i)
{
	int		k;
	int		size;

	k = 0;
	size = 0;
	while (s[i] && s[i] != '\'')
	{
		size++;
		i++;
	}
	i = 1;
	input->elem->content[1] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != '\'')
		input->elem->content[1][k++] = s[i++];
	if (i == 1)
		input->elem->content[1][k] = ' ';
	return (i);
}

int	no_quote_mgmt(t_input *input, char *s, int i)
{
	int		k;
	int		size;

	k = 0;
	size = 0;
	while (s[i] && s[i] != ' ')
	{
		size++;
		i++;
	}
	i = 0;
	ft_printf("size : [%d]\n", size);
	input->elem->content[1] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != ' ')
		input->elem->content[1][k++] = s[i++];
	return (i + 1);
}
