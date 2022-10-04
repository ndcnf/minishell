/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/04 13:59:13 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	char	*prompt;
	t_data	dt;
	int		i;
	int		j;
	int		quote;

	g_exit_stat = 0;
	prompt = NULL;
	b_init(&dt, envp);
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		//ft_printf("globale preco = %d\n", g_exit_stat);
		if (!prompt)
			exit(the_end("exit\n", EXIT_SUCCESS, 1));
		if (!prompt[0] || parsing_init(prompt, &dt) == NO_RESULT)
		{
			free(prompt);// a voir si necessaire avec les leaks
			continue ;
		}
		i = 0;
		while (i < dt.n_cmd)
		{
			j = 0;
			init_redir(&dt, i);
			while (j < dt.in[i].n_elem)
			{
				// redirection AVANT d'enlever les quotes, non ?
				trimquotes(&dt, "\"", i, j);
				quote = trimquotes(&dt, "\'", i, j);
				if (!quote)
					conv_var(&dt, i, j);
				if (checker_redir(&dt, i, j) == NO_RESULT)
					break ;
				j++;
			}
			if (dt.in[i].pos_red == NO_RESULT)
				break ;
			// UNIQUEMENT POUR TESTS //////////////////////////////////////////////////
			j = 0;
			ft_printf("n_elem [%d]\n", dt.in[i].n_elem);
			while (j < dt.in[i].n_elem)
			{
				ft_printf("new_elem [%d] : [%s]\n", j, dt.in[i].elem->cont[j]);
				j++;
			}
			int z = 0;
			while (z < dt.in[i].n_redir)
			{
				ft_printf("redir [%s] : [%s]\n", dt.in[i].red[z].chevron, dt.in[i].red[z].file);
				z++;
			}
			///////////////////////////////////////////////////////////////////////////
			cmd_selector(&dt, i++);
		}
		add_history(prompt);
		free(prompt);
		free_data(&dt);
		// POUR TESTS UNIQUEMENT //////////////////////////////////////////////
		//ft_printf("globale maintenant = %d\n", g_exit_stat);
		///////////////////////////////////////////////////////////////////////
	}
	free(dt.path);
}
