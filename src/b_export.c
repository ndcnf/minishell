/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:48:36 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/01 15:22:29 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_export(t_data *dt, int in)
{
	int		i;
	char	*key;
	char	*val;

	if (dt->in[in].n_elem == 1)
		sort_env(dt, in);
	else
	{
		i = 1;
		while (i < dt->in[in].n_elem)
		{
			key = parse_env(dt->in[in].elem->cont[i])[0];
			val = parse_env(dt->in[in].elem->cont[i])[1];
			add_key(dt, key, val);
			i++;
		}
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	update_key(t_data *dt, char *key, char *val, char **new_array)
{
	int		i;
	int		add_key;
	char	*exist_key;
	char	*new_val;

	i = 0;
	add_key = 1;
	new_val = define_val(key, val);
	while (i < dt->n_env)
	{
		exist_key = parse_env(dt->env[i])[0];
		if (!ft_strncmp(key, exist_key, ft_strlen(exist_key)))
		{
			add_key = 0;
			if (val)
				new_array[i] = new_val;
			else
				new_array[i] = ft_strdup(dt->env[i]);
		}
		else
			new_array[i] = ft_strdup(dt->env[i]);
		i++;
	}
	if (add_key)
	{
		new_array[i] = new_val;
		new_array[i + 1] = NULL;
		dt->n_env++;
	}
	else
		new_array[i] = NULL;
}

void	add_key(t_data *dt, char *key, char *val)
{
	char	**new_array;
	char	*new_val;
	int		add_key;
	int		i;

	add_key = 1;
	new_array = malloc(sizeof(char *) * (dt->n_env + 2));
	malloc_checker((char *)new_array);
	new_val = define_val(key, val);
	i = 0;
	update_key(dt, key, val, new_array);
	free(dt->env);
	dup_array_to_env(dt, new_array);
}

char	*define_val(char *key, char *val)
{
	char	*new_val;
	char	*new_key;
	char	*ret;

	if (val)
	{
		new_key = ft_strjoin(key, "=");
		new_val = ft_strtrim(val, "\"");
		ret = ft_strjoin(new_key, new_val);
		free(new_key);
		free(new_val);
	}
	else
		ret = ft_strdup(key);
	return (ret);
}
