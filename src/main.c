/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/24 17:37:13 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	t_builtins bs;

	char *args[3];
	args[0] = "/bin/echo";
	args[1] = "-n";
	args[2] = NULL;

	bs.args = malloc(sizeof(char *) * 3);
	bs.args[0] = strdup(args[0]);
	bs.args[1] = strdup(args[1]);
	bs.args[2] = NULL;
	b_echo(&bs);
	
	//lancer execve dans un fork, afin de pouvoir continuer le main apres l'execution
	if (execve(args[0], args, envp) == -1)
		perror("Something went wrong");
	//avec un fork, le message suivant sera execute. Sans le fork, il ne le sera qu'en cas d'erreur.
	printf("si tu me lis, ya une erreur\n");
}