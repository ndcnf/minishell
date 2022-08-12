/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/12 17:23:03 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char 	*prompt;
	t_input	*input;

	input = NULL;
	//ft_lstnew(cmd->content);

	t_builtins bs;

	// char *args[3];
	// args[0] = "/bin/echo";
	// args[1] = "-n";
	// args[2] = NULL;

	b_init(&bs, argc, argv, envp);
	/*if (ft_strncmp(argv[1], "echo", 4) == 0)
		b_echo(&bs);
	else if (ft_strncmp(argv[1], "pwd", 3) == 0)
		b_pwd(&bs);
	else if (ft_strncmp(argv[1], "cd", 2) == 0)
		b_cd(&bs);
	else if (ft_strncmp(argv[1], "exit", 4) == 0)
		b_exit(&bs);
	else if (ft_strncmp(argv[1], "env", 3) == 0)
		b_env(&bs);
	else if (ft_strncmp(argv[1], "export", 6) == 0)
		b_export(&bs);
	else if (ft_strncmp(argv[1], "unset", 5) == 0)
		b_unset(&bs);
	else
		printf("Command not found (yet)\n");*/
	prompt = NULL;

	while (1)
	{
		prompt = readline("\e[36mminishell$ \e[0m");
		parsing_init(prompt, input);
	}
	free(prompt);
	return(0);
}