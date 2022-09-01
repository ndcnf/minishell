/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/01 18:44:45 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main (int argc, char *argv[], char **envp)
{

	//--------- PARTIE MARLENE ---------
	(void)argc;
	(void)argv;
	(void)envp;
	char 	*prompt;
	t_input	*input;

	input = NULL;

	//ft_lstnew(cmd->content);
	// --------- PARTIE MARLENE ---------


	/* --------- PARTIE NADIA ---------
	t_builtins bs;
	//int	i;

	b_init(&bs, argc, argv, envp);
	if (argc == 1) // a modifier ensuite avec bs. et les bons crochets carres pour les autres conditions.
		printf("\n");
	else if (ft_strncmp(argv[1], "echo", 5) == 0)
		b_echo(&bs);
	else if (ft_strncmp(argv[1], "pwd", 4) == 0)
		b_pwd(&bs);
	else if (ft_strncmp(argv[1], "cd", 3) == 0)
		b_cd(&bs);
	else if (ft_strncmp(argv[1], "exit", 5) == 0)
		b_exit(&bs);
	else if (ft_strncmp(argv[1], "env", 4) == 0)
		b_env(&bs);
	else if (ft_strncmp(argv[1], "export", 7) == 0)
		b_export(&bs);
	else if (ft_strncmp(argv[1], "unset", 6) == 0)
		b_unset(&bs);
	// else if (ft_strchr(argv[2], '<'))
	// 	redir_input(&bs);
	// else if (ft_strchr(argv[2], '>'))
	// 	redir_output(&bs);
	// else if (ft_strncmp(argv[2], ">>", 2) == 0)
	// 	heredoc(&bs);
	// else if (ft_strncmp(argv[2], "<<", 2) == 0)
	// 	append_in(&bs);
	else
		printf("Command not found (yet)\n");

	freearray(bs.env, bs.n_env);
	freearray(bs.args, bs.n_args);

	//lancer execve dans un fork, afin de pouvoir continuer le main apres l'execution
	// if (execve(args[0], args, envp) == -1)
	// 	perror("Something went wrong");
	// //avec un fork, le message suivant sera execute. Sans le fork, il ne le sera qu'en cas d'erreur.
	// printf("si tu me lis, il y a une erreur\n");

	--------- PARTIE NADIA --------- */



	// --------- PARTIE MARLENE ---------
	prompt = NULL;
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		parsing_init(prompt, input);
		add_history(prompt);
	}
	free(prompt);
	// --------- PARTIE MARLENE ---------
}
