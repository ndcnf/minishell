/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/27 11:47:04 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_builtins *bs, int argc, char *argv[])
{
	int	i;

	bs->args = malloc(sizeof(char *) * (argc + 1));
	if (!bs->args)
		exit(EXIT_FAILURE);
	// Stocker temporairement les argv entres dans une structure
	// et decaler afin de ne plus avoir le nom "./minishell" en premier
	// argument
	i = 0;
	while (i < (argc - 1))
	{
		bs->args[i] = argv[i + 1];
		//printf("b_init[%d]: %s\n", i, bs->args[i]);
		i++;
	}
	bs->n_args = i;
	getcwd(bs->path, sizeof(bs->path));
}

// 'echo'				-> retour à la ligne
// 'echo -n'			-> rien, ligne suivante
// 'echo -n texte'		-> 'texte'
// 'echo texte'			-> 'texte\n'
// 'echo texte long'	-> 'texte long\n'
// 'echo -n texte long'	-> 'texte long'
// 'echo texte -n'		-> 'texte -n\n'
///////////////////////////////////////////////
int	b_echo(t_builtins *bs)
{
	int	i;

	if (bs->n_args == 1)
		printf("\n");
	if (bs->n_args >= 2)
	{
		if (ft_strncmp(bs->args[1], "-n", strlen(bs->args[1])) == 0)
		{
			if (bs->n_args != 2)
			{
				i = 2;
				while (i < bs->n_args)
				{
					printf("%s", bs->args[i]);
					i++;
					if (i != bs->n_args)
						printf(" ");
				}
				printf("\n");
			}
		}
		else
		{
			i = 1;
			while (i < bs->n_args)
			{
				printf("%s", bs->args[i]);
				i++;
				if (i != bs->n_args)
					printf(" ");
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	b_pwd(t_builtins *bs)
{
	if (getcwd(bs->path, sizeof(bs->path)) == NULL)
		perror("error");
	else
		printf("%s\n", bs->path);
	return (EXIT_SUCCESS);
}

// 'cd'			-> retour a /Users/(nom du user)
// 'cd ..'		-> retour un niveau avant (le prompt l'affiche)
// 'cd .'		-> on reste et fait rien
// 'cd (dir)	-> on va dans le dossier (dir)
int	b_cd(t_builtins *bs)
{
	printf("PATH avant : [%s]\n", bs->path);
	chdir(*bs->args);
	getcwd(bs->path, ft_strlen(bs->path));
	printf("PATH apres : [%s]\n", bs->path);
	return (EXIT_SUCCESS);
}