/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/03 15:23:17 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	char	*prompt;
	t_data	dt;
	int		i;
	int		j;
	int		k;
	int		quote;

	g_exit_stat = 0;
	prompt = NULL;
	b_init(&dt, envp);
	while (1)
	{
		prompt = readline("marynad$ ");
		// prompt = readline("\e[36mmarynad$ \e[0m");
		ft_printf("globale preco = %d\n", g_exit_stat);
		if (!prompt)
			exit(EXIT_SUCCESS);
		if (!prompt[0] || parsing_init(prompt, &dt) == NO_RESULT)
		{
			free(prompt);// a voir si necessaire avec les leaks
			continue ;
		}
		i = 0;
		while (i < dt.n_cmd)
		{
			j = 0;
			init_redir(&dt,i);
			while (j < dt.in[i].n_elem)
			{
				// redirection AVANT d'enlever les quotes, non ?
				trimquotes(&dt, "\"", i, j);
				quote = trimquotes(&dt, "\'", i, j);
				if (!quote)
					conv_var(&dt, i, j);
				checker_redir(&dt, i, j);
				j++;
			}
			dt.in[i].n_elem -= dt.in[i].n_redir * 2;
			// UNIQUEMENT POUR TESTS //////////////////////////////////////////////////
			// j = 0;
			// ft_printf("n_elem [%d]\n", dt.in[i].n_elem);
			// while (j < dt.in[i].n_elem)
			// {
			// 	ft_printf("new_elem [%d] : [%s]\n", j, dt.in[i].elem->cont[j]);
			// 	// if (dt.in[i].red)
			// 	// {
			// 	// 	int z = 0;
			// 	// 	while (z < dt.in[i].n_redir)
			// 	// 	{
			// 	// 		ft_printf("redir [%s] : [%s]\n", dt.in[i].red[z].chevron, dt.in[i].red[z].file);
			// 	// 		z++;
			// 	// 	}
			// 	// }
			// 	j++;
			// }
			///////////////////////////////////////////////////////////////////////////
			cmd_selector(&dt, i++);
		}
		add_history(prompt);
		free(prompt);
		i = 0;
		while (i < dt.n_cmd)
		{
			j = 0;
			while (j < dt.in[i].n_elem)
			{
				free(dt.in[i].elem->cont[j]);
				j++;
			}
			k = 0;
			while (k < dt.in[i].n_redir)
			{
				free(dt.in[i].red[k].chevron);
				free(dt.in[i].red[k].file);
				k++;
			}
			free(dt.in[i].red);
			free(dt.in[i].elem->cont);
			free(dt.in[i].elem);
			i++;
		}
		free(dt.in);
		// dt->in[i].elem = mal
		// dt->in[i].elem->cont

		// POUR TESTS UNIQUEMENT //////////////////////////////////////////////
		ft_printf("globale maintenant = %d\n", g_exit_stat);
		///////////////////////////////////////////////////////////////////////
	}
	free(dt.path);
	// free(prompt);
}
