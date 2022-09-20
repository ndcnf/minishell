/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:48:36 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/19 12:47:48 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	b_export(t_data *dt, int in)
{
	int		i;
	char	*key;
	char	*val;

	if (dt->in[in].n_elem == 1) //bs->nb_args avant
		sort_env(dt);
	else
	{
		i = 1;
		while (i < dt->in[in].n_elem) //bs->nb_args avant
		{
			key = get_key(dt, i);
			val = get_val(dt, i);
			add_key(dt, key, val);
			i++;
		}
		sort_env(dt);
	}
	return (EXIT_SUCCESS);
}

char	*get_key(t_data *dt, int pos)
{
	char	*new_key;
	int		i;

	new_key = malloc(sizeof(char) * ft_strlen(bs->args[pos] + 1)); //(bs->nb_args[pos] + 1) avant
	// new_key = malloc(sizeof(char) * ft_strlen(bs->args[pos]));
	malloc_checker(new_key);
	i = 0;
	while (bs->args[pos][i] != '=') //(bs->nb_args[pos][i] avant
	{
		new_key[i] = bs->args[pos][i];//(bs->nb_args[pos][i] avant
		i++;
	}
	new_key[i] = '\0';
	return (new_key);
	// if (new_key)
	//  	free(new_key);
}

char	*get_val(t_data *dt, int pos)
{
	char	*new_val;
	int		i;

	i = 0;
	new_val = ft_strchr(bs->args[pos], '=');
	return (new_val);
}

void	add_key(t_data *dt, char *key, char *val)
{
	char	**new_array;
	char	*new_val;
	char	*exist_key;
	int		add_key;
	int		i;

	add_key = 1;
	new_array = malloc(sizeof(char *) * (bs->n_env + 1) + 1);
	malloc_checker((char *)new_array);

	i = 0;
	while (i < bs->n_env)
	{
		new_array[i] = malloc(sizeof(char) * 2);
		i++;
	}

	new_val = define_val(key, val);
	i = 0;
	while (i < bs->n_env)
	{
		exist_key = parse_env(bs->env[i])[0];
		if (!ft_strncmp(key, exist_key, ft_strlen(exist_key)))
		{
			add_key = 0;
			if (val)
				new_array[i] = ft_strdup(new_val);
			else
				new_array[i] = ft_strdup(bs->env[i]);
		}
		else
			new_array[i] = ft_strdup(bs->env[i]);
		i++;
	}
	if (add_key)
	{
		new_array[i] = ft_strdup(new_val);
		new_array[i + 1] = NULL; //LEAKS
		bs->n_env++;
	}
	else
		new_array[i] = NULL;
	free(bs->env);
	dup_array_to_env(bs, new_array);
}

char	*define_val(char *key, char *val)
{
	char	*new_val;

	if (val)
	{
		new_val = ft_strjoin(key, "=");
		new_val = ft_strjoin(new_val, val);
	}
	else
		new_val = key;
	return (new_val);
}
