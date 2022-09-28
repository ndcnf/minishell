/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/28 15:43:21 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	char	*prompt;
	t_data	dt;
	int		i;

	prompt = NULL;
	b_init(&dt, envp);
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		if (!prompt)
			exit(0); // ------------------------------------------------------------valeur de sortie a gerer
		if (!prompt[0])
			continue;
		parsing_init(prompt, &dt);

		i = 0;
		while (i < dt.n_cmd)
		{
			trimquotes(&dt, "\"", i);
			conv_var(&dt, i);
			cmd_selector(&dt, i++); //remplacer le 0 plus tard pour savoir quel input est concerné
		}
		// exec(&dt, 0);
		//ft_printf("MAIN [%s]\n", &dt.in[0].elem->cont[1]);
		//builtins_selector(&dt, 0); //TESTS
		add_history(prompt);
	}
	free(prompt);
}
