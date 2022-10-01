/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/01 14:16:42 by nchennaf         ###   ########.fr       */
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
			while (j < dt.in[i].n_elem)
			{
				trimquotes(&dt, "\"", i, j);
				quote = trimquotes(&dt, "\'", i, j);
				if (!quote)
					conv_var(&dt, i, j);
				j++;
			}
			cmd_selector(&dt, i++);
		}
		add_history(prompt);
		free(prompt);

		// POUR TESTS UNIQUEMENT //////////////////////////////////////////////
		ft_printf("globale maintenant = %d\n", g_exit_stat);
		///////////////////////////////////////////////////////////////////////
	}
	// free(prompt);
}
