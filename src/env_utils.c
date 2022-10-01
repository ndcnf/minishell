/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:44:46 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/01 12:19:58 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_data *dt, char **elem)
{
	(void)dt;
	if (elem[1])
		printf("declare -x %s=\"%s\"\n", elem[0], elem[1]);
	else if (elem[0])
		printf("declare -x %s\n", elem[0]);
}

char	**parse_env(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	return (elem);
}

void	sort_env(t_data *dt, int in)
{
	int		i;
	int		j;
	char	*tempura;
	char	**export;

	export = malloc(sizeof(char *) * dt->n_env);
	malloc_checker((char *)export);
	i = -1;
	while (++i < dt->n_env)
		export[i] = ft_strdup(dt->env[i]);
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
	if (dt->in[in].n_elem == 1)
	{
		i = 0;
		while (i < dt->n_env)
			print_env(dt, parse_env(export[i++]));
	}
	freearray(export, dt->n_env);
}

// char	**dup_env()

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

void	freearray(char **m, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(m[i++]);
	free(m);
}
