/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:55:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/31 15:19:06 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Stocker temporairement les argv entres dans une structure
// et decaler afin de ne plus avoir le nom "./minishell" en premier
// argument
void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[])
{
	int	i;

	bs->args = malloc(sizeof(char *) * (argc - 1));
	malloc_checker((char *)bs->args);
	bs->n_args = argc - 1;
	i = 1;
	while (i < argc)
	{
		bs->args[i - 1] = ft_strdup(argv[i]);
		malloc_checker(bs->args[i - 1]);
		i++;
	}

	i = 0;
	while (envp[i] != NULL)
		i++;
	bs->n_env = i;
	bs->env = malloc(sizeof(char *) * bs->n_env);
	malloc_checker((char *)bs->env);
	i = 0;
	while (i < bs->n_env)
	{
		bs->env[i] = ft_strdup(envp[i]);
		malloc_checker(bs->env[i]);
		i++;
	}
}

void	malloc_checker(char *s)
{
	if (!s)
		exit(EXIT_FAILURE);
}
