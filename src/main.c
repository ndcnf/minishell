/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 16:20:18 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	//--------- PARTIE MARLENE ---------
	(void)argv;
	(void)envp;
	if (argc > 1)
	{
		ft_printf("\033[31mARG_ERROR\n\033[31m");
		return (1);
	}
	if (envp)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		ft_termios();
		prompt(envp);
	}

	// --------- PARTIE MARLENE ---------

	/* --------- PARTIE NADIA ---------
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
