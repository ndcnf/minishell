/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/09 18:32:01 by mthiesso         ###   ########.fr       */
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
	{
		printf("DEGAGE\n");
		exit(0); // A CHANGER CAR TU ES PAS SI COOL :'(
	}
	s = ft_strtrim(s, " ");
	return (s);
}

void	parsing_elem(t_input *input, char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (s[0])
	{
		i = first_elem(input, s, s[0]);
		if (input->nb_elem > 3)
			n = 3;
	}
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (s[i] == '\'')
		{
			input->elem->content[n] = ft_strdup("\'");
			i = s_quotes_mgmt(input, s, (i + 1), (n + 1));
			input->elem->content[n + 2] = ft_strdup("\'");
		}
		else if (s[i] == '\"')
		{
			input->elem->content[n] = ft_strdup("\"");
			i = d_quotes_mgmt(input, s, (i + 1), (n + 1));
			input->elem->content[n + 2] = ft_strdup("\"");
		}
		else
			i = no_quote_mgmt(input, s, i, n);
		n++;
	}
	n = 0;
	while (n < input->nb_elem)
	{
		ft_printf("elem [%d] : [%s]\n", n, input->elem->content[n]);
		n++;
	}
}

int	first_elem(t_input *input, char *s, char c)
{
	int	i;

	i = 0;
	if (c == '\"')
	{
		input->elem->content[0] = ft_strdup("\"");
		i = d_quotes_mgmt(input, s, 1, 1);
		input->elem->content[2] = ft_strdup("\"");
	}
	else if (c == '\'')
	{
		input->elem->content[0] = ft_strdup("\'");
		i = s_quotes_mgmt(input, s, 1, 1);
		input->elem->content[2] = ft_strdup("\'");
	}
	else
	{
		input->elem->content[0] = ft_strdup("X");
		i = no_quote_mgmt(input, s, 0, 1);
		input->elem->content[2] = ft_strdup("X");
	}
	return (i);
}

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
	i = j; //i = 0;
	input->elem->content[n] = malloc(sizeof(char) * size);
	while (s[i] && s[i] != ' ')
		input->elem->content[n][k++] = s[i++];
	return (i);
}
