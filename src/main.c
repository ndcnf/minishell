/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/08 13:25:44 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[], char **envp)
{
	// (void)argc;
	// (void)argv;
	// (void)envp;

	t_builtins bs;

	// char *args[3];
	// args[0] = "/bin/echo";
	// args[1] = "-n";
	// args[2] = NULL;

	ft_printf("TEST\n");
	b_init(&bs, argc, argv, envp);
	if (ft_strncmp(argv[1], "echo", 4) == 0)
		b_echo(&bs);
	else if (ft_strncmp(argv[1], "pwd", 3) == 0)
		b_pwd(&bs);
	else if (ft_strncmp(argv[1], "cd", 2) == 0)
		b_cd(&bs);
	else if (ft_strncmp(argv[1], "exit", 4) == 0)
		b_exit(&bs);
	else if (ft_strncmp(argv[1], "env", 3) == 0)
		b_env(&bs);
	else
		printf("Command not found (yet)\n");
	
	//lancer execve dans un fork, afin de pouvoir continuer le main apres l'execution
	// if (execve(args[0], args, envp) == -1)
	// 	perror("Something went wrong");
	// //avec un fork, le message suivant sera execute. Sans le fork, il ne le sera qu'en cas d'erreur.
	// printf("si tu me lis, il y a une erreur\n");
}