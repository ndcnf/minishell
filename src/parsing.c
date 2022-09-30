/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/30 11:47:04 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_init(char *args, t_data *dt)
{
	int			i;

	i = 0;
	dt->n_cmd = 0;
	if (args)
	{
		dt->n_cmd = 1;
		if (nb_cmd(dt, args, i) == NO_RESULT)
			return (NO_RESULT);
	}
	dt->in = malloc(sizeof(t_input) * dt->n_cmd);
	i = -1;
	while (++i < dt->n_cmd)
		dt->in[i].cont = ft_split_ex(args, '|')[i];
	i = 0;
	while (i < dt->n_cmd)
	{
		dt->in[i].n_elem = 1;
		space_counter(&dt->in[i], dt->in[i].cont);
		dt->in[i].elem = malloc(sizeof(t_elem));
		dt->in[i].elem->cont = malloc(sizeof(char *) * (dt->in[i].n_elem + 1));
		parsing_elem(dt, dt->in[i].cont, i);
		i++;
	}
	return (EXIT_SUCCESS);
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
	return (s);
}

void	parsing_elem(t_data *dt, char *s, int in)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
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

	s = ft_substr(s, skip_spaces(s, i), ft_strlen(s));
	i = 0;
	j = malloc_elem(in, s, i, n);
	while (i < j)
	{
		i = into_elem_quotes(in, s, i, n);
		if (s[i] == ' ')
			break ;
		in->elem->cont[n][i] = s[i];
		i++;
	}
	in->elem->cont[n][i] = '\0';
	return (i);
}
