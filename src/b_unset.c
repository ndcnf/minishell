/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:22:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/22 18:07:26 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_builtins *bs)
{
	int		i;
	char	*key;

	i = 0;
	if (bs->n_args == 1)
		return (EXIT_SUCCESS);
	else
	{
		i = 1;
		while (i < bs->n_args)
		{
			key = get_key(bs, i);
			remove_key(bs, key);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

void	remove_key(t_builtins *bs, char *key)
{
	char	**new_array;
	char	*exist_key;
	int		rem_key;
	int		i;
	int		j;

	rem_key = 0;
	new_array = malloc(sizeof(char *) * (bs->n_env));
	malloc_checker((char *)new_array);
	i = 0;
	j = 0;
	while (i < bs->n_env)
	{
		exist_key = parse_env(bs->env[i])[0];
		if (ft_strncmp(key, exist_key, ft_strlen(exist_key)))
			new_array[j++] = ft_strdup(bs->env[i]);
		else
			rem_key = 1;
		i++;
	}
	new_array[j] = NULL;
	if (rem_key == 1)
		bs->n_env--;
	free(bs->env);
	dup_array_to_env(bs, new_array);
}
