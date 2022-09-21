/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:26 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/21 15:12:33 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	char 	*prompt;
	t_data	dt;

	prompt = NULL;
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		parsing_init(prompt, &dt);
		//cmd_selecter(&dt, 0); //remplacer le 0 plus tard pour savoir quel input est concerné
		add_history(prompt);
	}
	free(prompt);
}