/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/16 14:51:17 by mthiesso         ###   ########.fr       */
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
	// while (i < dt->n_cmd)
	// {
	// 	dt->in[i].n_elem = 1;
	// 	dt->in[i].cont = parse_cmd(dt, dt->in[i].cont, i);
	// 	space_counter(&dt->in[i], dt->in[i].cont);
	// 	dt->in[i].elem = malloc(sizeof(t_elem));
	// 	dt->in[i].elem->cont = malloc(sizeof(char *) * dt->in[i].n_elem);
	// 	parsing_elem(dt, dt->in[i].cont, i);
	// 	i++;
	// }

	while (i < dt->n_cmd)
	{
		dt->in[i].n_elem = 1;
		space_counter(&dt->in[i], dt->in[i].cont);
		dt->in[i].elem = malloc(sizeof(t_elem));
		dt->in[i].elem->cont = malloc(sizeof(char *) * dt->in[i].n_elem);
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
	if (s[0])
	{
		i = first_elem(dt, s, in);
	}
	// while (s[i])
	// {
	// 	i = skip_spaces(s, i);
	// 	if (s[i] == '\'')
	// 	{
	// 		//dt->in[in].elem->cont[n] = ft_strdup("\'");
	// 		i = s_quotes_mgmt(&dt->in[in], s, (i + 1), (n + 1));
	// 		//dt->in[in].elem->cont[n + 2] = ft_strdup("\'");
	// 	}
	// 	else if (s[i] == '\"')
	// 	{
	// 		//dt->in[in].elem->cont[n] = ft_strdup("\"");
	// 		i = d_quotes_mgmt(&dt->in[in], s, i, n);
	// 		//dt->in[in].elem->cont[n + 2] = ft_strdup("\"");
	// 	}
	// 	else
	// 		i = no_quote_mgmt(&dt->in[in], s, i, n);
	// 	n++;
	// }
	//cmd_selecter(dt, 0);
	n = 0;
	// while (n < dt->in[in].n_elem) // UNIQUEMENT POUR TESTS
	// {
	ft_printf("elem [%d] : [%s]\n", n, dt->in[in].elem->cont[0]);
	// 	n++;
	// }
}

int	first_elem(t_data *dt, char *s, int in)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = ft_substr(s, skip_spaces(s, i), ft_strlen(s));
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
	dt->in[in].elem->cont[0] = malloc(sizeof(char) * j + 1);
	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		while (i < j)
		{
			dt->in[in].elem->cont[0][i] = s[i];
			i++;
		}
	}
	else
	{
		while (i < j)
		{
			if (s[i] == ' ')
				break ;
			dt->in[in].elem->cont[0][i] = s[i];
			i++;
		}
	}
	dt->in[in].elem->cont[0][i] = '\0';

	

	// while (s[i] && s[i] != ' ')
	// {
	// 	if (s[i] == '\"')
	// 		i++;
	// 	j++;
	// 	i++;
	// }
	// tmp = malloc(sizeof(char) * j + 1);
	// i = 0;
	// j = 0;
	// while (s[i] && s[i] != ' ')
	// {
	// 	if (s[i] == '\"')
	// 		i++;
	// 	tmp[j++] = ft_tolower(s[i++]);
	// }
	return (i);
}
