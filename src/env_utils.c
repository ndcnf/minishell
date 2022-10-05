/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:44:46 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 21:47:21 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_data *dt, int in, char **elem)
{
	int		i;
	char	**export;

	if (dt->in[in].n_elem == 1)
	{
		i = 0;
		while (i < dt->n_env)
		{
			export = parse_env(elem[i]);
			if (export[1])
				ft_printf("declare -x %s=\"%s\"\n", export[0], export[1]);
			else if (export[0])
				ft_printf("declare -x %s\n", export[0]);
			i++;
			freearray(export, 2);
		}
	}
}

char	**parse_env(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	return (elem);
}

char	**dup_env(t_data *dt)
{
	int		i;
	char	**export;

	export = malloc(sizeof(char *) * dt->n_env);
	malloc_checker((char *)export);
	i = 0;
	while (i < dt->n_env)
	{
		export[i] = ft_strdup(dt->env[i]);
		i++;
	}
	return (export);
}

void	sort_env(t_data *dt, int in)
{
	int		i;
	int		j;
	char	*tempura;
	char	**export;

	export = dup_env(dt);
	i = 0;
	while (i < dt->n_env)
	{
		j = i + 1;
		while (j < dt->n_env)
		{
			if (ft_strncmp(export[j], export[i], MAX_PATH) < 0)
			{
				tempura = export[i];
				export[i] = export[j];
				export[j] = tempura;
			}
			j++;
		}
		i++;
	}
	print_env(dt, in, export);
	freearray(export, dt->n_env);
}

void	dup_array_to_env(t_data *dt, char **array)
{
	int	i;

	dt->env = malloc (sizeof(char *) * (dt->n_env + 1));
	malloc_checker((char *)dt->env);
	i = -1;
	while (++i < dt->n_env)
		dt->env[i] = array[i];
	dt->env[i] = NULL;
	free(array);
}
