/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:55:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/12 13:41:42 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Stocker temporairement les argv entres dans une structure
// et decaler afin de ne plus avoir le nom "./minishell" en premier
// argument
void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[])
{
	int	i;

	bs->args = malloc(sizeof(char *) * (argc + 1));
	malloc_checker((char *)bs->args);
	i = 0;
	while (i < argc)
	{
		bs->args[i] = ft_strdup(argv[i]);
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
		i++;
	}
	i = 0;
	while (i < (argc - 1))
	{
		bs->args[i] = argv[i + 1];
		i++;
	}
	bs->n_args = i;
}

void	malloc_checker(char *s)
{
	if (!s)
		exit(EXIT_FAILURE);
}
