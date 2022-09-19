/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/19 13:43:47 by nchennaf         ###   ########.fr       */
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
	t_data	dt;

	prompt = NULL;
	b_init(&dt, envp);
	while (1)
	{
		prompt = readline("\e[36mmarynad$ \e[0m");
		parsing_init(prompt, &dt);
		//ft_printf("MAIN [%s]\n", &dt.in[0].elem->cont[1]);
		//builtins_selector(&dt, 0); //TESTS
		b_env(&dt);
		// b_cd(&dt, 0); // test only
		add_history(prompt);
	}
	free(prompt);
	// --------- PARTIE MARLENE ---------


	/* --------- PARTIE NADIA ---------
	t_builtins bs;
	//int	i;

	b_init(&bs, argc, argv, envp);
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

	//lancer execve dans un fork, afin de pouvoir continuer le main apres l'execution
	// if (execve(args[0], args, envp) == -1)
	// 	perror("Something went wrong");
	// //avec un fork, le message suivant sera execute. Sans le fork, il ne le sera qu'en cas d'erreur.
	// printf("si tu me lis, il y a une erreur\n");

	--------- PARTIE NADIA --------- */
}
