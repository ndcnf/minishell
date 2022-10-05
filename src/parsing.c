/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/10/05 15:03:52 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing_init(char *args, t_data *dt)
{
	int		i;
	char	**input;

	i = 0;
	dt->n_cmd = 0;
	if (args)
	{
		dt->n_cmd = 1;
		if (nb_cmd(dt, args, i) == NO_RESULT)
			return (NO_RESULT);
	}
	dt->in = ft_calloc(sizeof(t_input), dt->n_cmd);
	i = -1;
	input = ft_split_ex(args, '|');
	while (++i < dt->n_cmd)
	{
		if (input[i] == NULL && dt->n_cmd > 1)
		{
			the_end(ERR_TOKEN, ERR_REDIR, 1);
			return (NO_RESULT);
		}
		dt->in[i].cont = input[i];
	}
	i = -1;
	while (++i < dt->n_cmd)
	{
		dt->in[i].n_elem = 1;
		space_counter(&dt->in[i], dt->in[i].cont);
		dt->in[i].elem = malloc(sizeof(t_elem));
		dt->in[i].elem->cont = malloc(sizeof(char *) * (dt->in[i].n_elem + 1));
		parsing_elem(dt, dt->in[i].cont, i);
	}
	freearray(input, dt->n_cmd);
	return (EXIT_SUCCESS);
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
	// UNIQUEMENT POUR TESTS //////////////////////////////////////////////////
	// n = 0;
	// while (n < dt->in[in].n_elem)
	// {
	// 	ft_printf("elem [%d] : [%s]\n", n, dt->in[in].elem->cont[n]);
	// 	n++;
	// }
	///////////////////////////////////////////////////////////////////////////
}

int	each_elem(t_input *in, char *s, int i, int n)
{
	int		j;

	s = ft_strtrim(s, " \t\n\r");
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
	// printf("[%s]\n", in->elem->cont[n]);
	in->elem->cont[n][i] = '\0';
	free(s);
	return (i);
}
