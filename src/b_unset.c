/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:22:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/22 17:18:11 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	b_unset(t_data *dt, int in)
{
	int		i;
	char	*key;

	i = 0;
	if (dt->in[in].n_elem == 1)
		return (EXIT_SUCCESS);
	else
	{
		i = 1;
		while (i < dt->in[in].n_elem)
		{
			key = parse_env(dt->in[in].elem->cont[i])[0];
			remove_key(dt, key);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

void	remove_key(t_data *dt, char *key)
{
	char	**new_array;
	char	*exist_key;
	int		rem_key;
	int		i;
	int		j;

	rem_key = 0;
	new_array = malloc(sizeof(char *) * (dt->n_env));
	malloc_checker((char *)new_array);
	i = 0;
	j = 0;
	while (i < dt->n_env)
	{
		exist_key = parse_env(dt->env[i])[0];
		if (ft_strncmp(key, exist_key, ft_strlen(exist_key)))
			new_array[j++] = ft_strdup(dt->env[i]);
		else
			rem_key = 1;
		i++;
	}
	new_array[j] = NULL;
	if (rem_key == 1)
		dt->n_env--;
	free(dt->env);
	dup_array_to_env(dt, new_array);
}
