/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/01 17:19:17 by nchennaf         ###   ########.fr       */
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

	// Simulation de prompt pour tester une commande et son argument
	// Dans ce cas, il y aura toujours une commande ET un argument (pas de vide)
	// Pour le lancer : METTRE DEUX ARGUMENTS, sinon heap overflow
	while (1)
	{
		free(bs.args[0]);
		bs.args[0] = readline("cmd>");
		free(bs.args[1]);
		bs.args[1] = readline("arg>");
		// /*
		if (bs.n_args == 1 || (!bs.args[0]))
			printf("\n");
		else if (ft_strncmp(bs.args[0], "echo", 5) == 0)
			b_echo(&bs);
		else if (ft_strncmp(bs.args[0], "pwd", 4) == 0)
			b_pwd(&bs);
		else if (ft_strncmp(bs.args[0], "cd", 3) == 0)
			b_cd(&bs);
		else if (ft_strncmp(bs.args[0], "exit", 5) == 0)
			b_exit(&bs);
		else if (ft_strncmp(bs.args[0], "env", 4) == 0)
			b_env(&bs);
		else if (ft_strncmp(bs.args[0], "export", 7) == 0)
			b_export(&bs);
		else if (ft_strncmp(bs.args[0], "unset", 6) == 0)
			b_unset(&bs);
		// else if (ft_strchr(argv[2], '<'))
		// 	redir_input(&bs);
		// else if (ft_strchr(argv[2], '>'))
		// 	redir_output(&bs);
		// else if (ft_strncmp(argv[2], ">>", 2) == 0)
		// 	heredoc(&bs);
		// else if (ft_strncmp(argv[2], "<<", 2) == 0)
		// 	append_in(&bs);
		// else if (ft_strchr(argv[2], '$'))
		else
			printf("Command not found (yet)\n");
		conv_var(&bs);
	}
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
