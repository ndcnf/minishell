/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:22:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/03 19:25:13 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_data *dt, int in)
{
	int		i;
	char	**splited;

	i = 0;
	if (dt->in[in].n_elem == 1)
		return (the_end(NULL, EXIT_SUCCESS, 00));
	else
	{
		i = 1;
		while (i < dt->in[in].n_elem)
		{
			splited = parse_env(dt->in[in].elem->cont[i]);
			remove_key(dt, splited[0]);
			freearray(splited, 2);
			i++;
		}
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	remove_key(t_data *dt, char *key)
{
	char	**new_array;
	char	**exist_key;
	int		rem_key;
	int		i;
	int		j;

	rem_key = 0;
	new_array = malloc(sizeof(char *) * (dt->n_env + 1));
	malloc_checker((char *)new_array);
	i = -1;
	j = 0;
	while (++i < dt->n_env)
	{
		exist_key = parse_env(dt->env[i]);
		if (ft_strncmp(key, exist_key[0], ft_strlen(exist_key[0])))
			new_array[j++] = ft_strdup(dt->env[i]);
		else
			rem_key = 1;
		freearray(exist_key, 2);
	}
	new_array[j] = NULL;
	if (rem_key == 1)
		dt->n_env--;
	freearray(dt->env, dt->n_env + 1);
	dup_array_to_env(dt, new_array);
}
