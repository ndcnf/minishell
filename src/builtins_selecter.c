/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_selecter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/19 12:58:54 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_selector(t_data *dt, int i) // rajouter i pour savoir dans quel input on est
{
	// (void)i;
	// if (dt->n_cmd == 0) // cette condition devra etre faite au debut meme du programme, pas ici
	// 	printf("\n");
	// else if (ft_strncmp(dt->in[in]->elem->content[1], "echo", 5) == 0)
	// 	b_echo(&input);
	// else if (ft_strncmp(input->elem->content[1], "pwd", 4) == 0)
	// 	b_pwd(&input);
	// else if (ft_strncmp(input->elem->content[1], "cd", 3) == 0)
	// 	b_cd(&input);
	// else if (ft_strncmp(input->elem->content[1], "exit", 5) == 0)
	// 	b_exit(&input);
	// else if (ft_strncmp(input->elem->content[1], "env", 4) == 0)
	// 	b_env(&input);
	// else if (ft_strncmp(input->elem->content[1], "export", 7) == 0)
	// 	b_export(&input);
	// else if (ft_strncmp(input->elem->content[1], "unset", 6) == 0)
	// 	b_unset(&input);
	// else
	// 	printf("Command not found (yet)\n");

	ft_printf("SELECTOR[%s]\n", dt->in[i].elem->cont[1]);

	if (dt->n_cmd == 0) // cette condition devra etre faite au debut meme du programme, pas ici
		ft_printf("\n");
	// else if (ft_strncmp(dt->in[in]->elem->content[0], "echo", 5) == 0)
	// 	b_echo(&dt);
	else if (ft_strncmp(dt->in[i].elem->cont[1], "pwd", 4) == 0)
		b_pwd(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[1], "cd", 3) == 0)
		b_cd(dt, i);
	// else if (ft_strncmp(dt->in[i].elem->cont[1], "exit", 5) == 0)
	// 	b_exit(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[1], "env", 4) == 0)
		b_env(dt);
	// else if (ft_strncmp(dt->in[i].elem->cont[1], "export", 7) == 0)
	// 	b_export(dt);
	// else if (ft_strncmp(dt->in[i].elem->cont[1], "unset", 6) == 0)
	// 	b_unset(dt);
	else
		printf("Command [%s] not found (yet)\n", dt->in[i].elem->cont[1]);


	// freearray(bs.env, bs.n_env);
	// freearray(bs.args, bs.n_args);
}
