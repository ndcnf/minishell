/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/24 15:01:21 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;

	char *args[3];
	args[0] = "/bin/ls";
	args[1] = "-lh";
	args[2] = NULL;
	printf("%s\n", envp[0]);
	//lancer execve dans un fork, afin de pouvoir continuer le main apres l'execution
	if (execve(args[0], args, envp) == -1)
		perror("Something went wrong");
	//avec un fork, le message suivant sera execute. Sans le fork, il ne le sera qu'en cas d'erreur.
	printf("si tu me lis, ya une erreur\n");
}