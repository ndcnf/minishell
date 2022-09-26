/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:55:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/22 18:07:22 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_data *dt, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	dt->n_env = i;
	dt->env = malloc(sizeof(char *) * dt->n_env);
	malloc_checker((char *)dt->env);
	i = 0;
	while (i < dt->n_env)
	{
		dt->env[i] = ft_strdup(envp[i]);
		malloc_checker(dt->env[i++]);
	}
	i = 0;
	while (ft_strncmp(parse_env(dt->env[i])[0], "PATH", 4))
		i++;
	dt->path = ft_substr(ft_strdup(dt->env[i]), 5, ft_strlen(dt->env[i]));
	// i = 0;
	// while (i < dt->n_env)
	// {
	// 	ft_printf("oldpwd [%s]\n", ft_strnstr(dt->env[i], "OLDPWD", ft_strlen(dt->env[i])));
	// 	i++;
	// }
}

void	malloc_checker(char *s)
{
	if (!s)
		exit(EXIT_FAILURE);
}

// void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[])
// {
// 	int	i;

// 	bs->args = malloc(sizeof(char *) * (argc - 1));
// 	malloc_checker((char *)bs->args);
// 	bs->n_args = argc - 1;
// 	i = 1;
// 	while (i < argc)
// 	{
// 		bs->args[i - 1] = ft_strdup(argv[i]);
// 		malloc_checker(bs->args[i - 1]);
// 		i++;
// 	}

// 	i = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	bs->n_env = i;
// 	bs->env = malloc(sizeof(char *) * bs->n_env);
// 	malloc_checker((char *)bs->env);
// 	i = 0;
// 	while (i < bs->n_env)
// 	{
// 		bs->env[i] = ft_strdup(envp[i]);
// 		malloc_checker(bs->env[i]);
// 		i++;
// 	}
// }
