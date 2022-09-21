/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/21 18:12:51 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_init(char *args, t_data *dt)
{
	int			i;

	i = 0;
	dt->n_cmd = 0;
	if (ft_strncmp(args, "", 1) == 0)
	{
		printf("");
		return ;
	}
	dt->n_cmd = 1;
	while (args[i])
	{
		if (args[i] == '\"' || args[i] == '\'')
			i = is_quotes(args, i);
		if (args[i] == '|')
			dt->n_cmd++;
		i++;
	}
	dt->in = malloc(sizeof(t_input) * dt->n_cmd);
	i = -1;
	while (++i < dt->n_cmd)
		dt->in[i].cont = ft_split_ex(args, '|')[i];
	i = 0;
	ft_printf("n_cmd : [%d]\n", dt->n_cmd);
	while (i < dt->n_cmd)
	{
		dt->in[i].n_elem = 1;
		space_counter(&dt->in[i], dt->in[i].cont);
		dt->in[i].elem = malloc(sizeof(t_elem));
		dt->in[i].elem->cont = malloc(sizeof(char *) * (dt->in[i].n_elem + 1));
		parsing_elem(dt, dt->in[i].cont, i);
		ft_printf("n_elem : [%d]\n", dt->in[i].n_elem);
		i++;
	}
}

char	*parse_cmd(t_data *dt, char *s, int in)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_quotes(&dt->in[in], s) == 1)
	{
		printf("DEGAGE\n");
		exit(0); // A CHANGER CAR TU ES PAS SI COOL :'(
	}
	//s = ft_strtrim(s, " ");
	return (s);
}

void	parsing_elem(t_data *dt, char *s, int in)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	// if (s[0])
	// {
	// 	i = each_elem(&dt->in[in], s, i, n);
	// 	n++;
	// }
	while (s[i] && n < dt->in[in].n_elem)
	{
		i += (each_elem(&dt->in[in], s, i, n++));
		if (n == dt->in[in].n_elem)
			break ;
		i++;
	}
	dt->in[in].elem->cont[n] = NULL;
	//cmd_selecter(dt, 0);
	n = 0;
	while (n < dt->in[in].n_elem) // UNIQUEMENT POUR TESTS
	{
		ft_printf("elem [%d] : [%s]\n", n, dt->in[in].elem->cont[n]);
		n++;
	}
}

int	each_elem(t_input *in, char *s, int i, int n)
{
	int		j;
	int		g;

	j = 0;
	g = i;
	s = ft_substr(s, skip_spaces(s, i), ft_strlen(s));
	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
		j = (is_quotes(s, i) + 1);
	else
	{
		while (s[i])
		{
			if (s[i] == ' ')
				break ;
			i++;
			j++;
		}
	}
	in->elem->cont[n] = malloc(sizeof(char) * j + 1);
	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		while (i < j)
		{
			in->elem->cont[n][i] = s[i];
			i++;
		}
	}
	else
	{
		while (i < j)
		{
			if (s[i] == ' ')
				break ;
			in->elem->cont[n][i] = s[i];
			i++;
		}
	}
	in->elem->cont[n][i] = '\0';
	return (i);
}
