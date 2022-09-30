/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:55:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 15:47:53 by nchennaf         ###   ########.fr       */
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
	dt->env = malloc(sizeof(char *) * (dt->n_env + 1));
	malloc_checker((char *)dt->env);
	i = 0;
	while (i < dt->n_env)
	{
		dt->env[i] = ft_strdup(envp[i]);
		malloc_checker(dt->env[i++]);
	}
	dt->env[i] = NULL;
	i = 0;
	while (ft_strncmp(parse_env(dt->env[i])[0], "PATH", 4))
		i++;
	dt->path = ft_substr(ft_strdup(dt->env[i]), 5, ft_strlen(dt->env[i]));
}

void	malloc_checker(char *s)
{
	if (!s)
		exit(the_end(ERR_MALL, EXIT_FAILURE));
}
