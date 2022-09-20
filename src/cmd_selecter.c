/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selecter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/13 10:33:27 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_selecter(t_data *dt, int i)
{
	// if (dt->n_cmd == 0) // cette condition devra etre faite au debut meme du programme, pas ici
	// 	printf("\n");
	if (ft_strncmp(dt->in[i].elem->cont[1], "echo", 5) == 0)
		b_echo(dt, i);
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
	else
		printf("Command not found (yet)\n");
	// freearray(bs.env, bs.n_env);
	// freearray(bs.args, bs.n_args);
}
