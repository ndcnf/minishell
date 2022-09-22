/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/22 11:27:01 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	char	*prompt;
	t_data	dt;

	prompt = NULL;
	b_init(&dt, envp);
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		parsing_init(prompt, &dt);
		exec(&dt, 0);
		//ft_printf("MAIN [%s]\n", &dt.in[0].elem->cont[1]);
		//builtins_selector(&dt, 0); //TESTS
		//b_pwd(&dt);
		//b_cd(&dt, 0); // in = 0 actuellement, juste pour les tests
		//cmd_selecter(&dt, 0); //remplacer le 0 plus tard pour savoir quel input est concerné
		add_history(prompt);
	}
	free(prompt);
}
