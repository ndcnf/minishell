/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:55:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/06 15:57:59 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	b_init(t_data *dt, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	dt->n_env = i;
	dt->env = malloc(sizeof(char *) * (dt->n_env + 1));
	malloc_checker((char *)dt->env);
	i = 0;
	while (i < dt->n_env)
	{
		dt->env[i] = ft_strdup(envp[i]);
		malloc_checker(dt->env[i++]);
	}
	dt->env[i] = NULL;
}

void	malloc_checker(char *s)
{
	if (!s)
		exit(the_end(ERR_MALL, EXIT_FAILURE, 1));
}

void	freearray(char **m, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(m[i++]);
	free(m);
}
