/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:48:36 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/11 11:59:38 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 'export'				-> affiche liste des variables environnement, triees par ASCII
// 'export bonjour'		-> cree la variable bonjour seule, rien ne s'affiche. Cette info ne sera pas ajoutee lors de l'affichage de env, mais dans export oui
// 'export test=texte	-> cree la variable test="texte", rien ne s'affiche. Cette info sera ajoutee lors de l'affichage de env et export
//////////////////////////////////////////////////////////////////////////////////////
int		b_export(t_builtins *bs)
{
	int		i;
	char	*key;
	char	*val;

	if (bs->n_args == 1)
		sort_env(bs);
	else
	{
		i = 1;
		while (i < bs->n_args)
		{
			key = get_key(bs, i);
			val = get_val(bs, i);
			mod_key(bs, key, val);
			//add_key(bs, key, val);
			//si on ajoute un nouvel element dans le tableau alors n_env++
			//bs->n_env++;
			i++;
		}
		sort_env(bs); //VERIFICATION UNIQUEMENT
	}
	return (EXIT_SUCCESS);
}

char	*get_key(t_builtins *bs, int pos)
{
	char	*new_key;
	int		i;

	new_key = malloc(sizeof(char) * ft_strlen(bs->args[pos]));
	malloc_checker(new_key);
	i = 0;
	while (bs->args[pos][i] != '=')
	{
		new_key[i] = bs->args[pos][i];
		i++;
	}
	new_key[i] = '\0';
	return (new_key);
	// if (new_key)
	// 	free(new_key);
}

char	*get_val(t_builtins *bs, int pos)
{
	char	*new_val;
	int		i;

	i = 0;
	new_val = ft_strchr(bs->args[pos], '=');
	return (new_val);
}

void	add_key(t_builtins *bs, char *key, char *val)
{
	char	**new_array;
	char	*new_val;
	int		i;

	new_array = malloc(sizeof(char *) * (bs->n_env + 1));
	malloc_checker((char *)new_array);
	if (val)
	{
		key = ft_strjoin(key, "=");
		new_val = ft_strjoin(key, val);
	}
	else
		new_val = key;
	i = 0;
	while (i < bs->n_env)
	{
		new_array[i] = ft_strdup(bs->env[i]);
		i++;
	}
	new_array[i] = new_val;
	new_array[i + 1] = NULL;
	free(bs->env);
	dup_array_to_env(bs, new_array);
}

void	mod_key(t_builtins *bs, char *key, char *val)
{
	char	**new_array;
	char	*new_val;
	char	*exist_key;
	char	*key_val;
	int		add_key;
	int		i;

	add_key = 1;
	new_array = malloc(sizeof(char *) * (bs->n_env + 1));
	malloc_checker((char *)new_array);
	if (val)
	{
		key_val = ft_strjoin(key, "=");
		new_val = ft_strjoin(key_val, val);
	}
	else
		new_val = key;
	i = 0;
	while (i < bs->n_env)
	{
		exist_key = parse_env(bs->env[i])[0];
		if (!ft_strncmp(key, exist_key, ft_strlen(exist_key)))
		{
			add_key = 0;
			if (val)
				new_array[i] = new_val;
			else
				new_array[i] = key;
		}
		else
			new_array[i] = ft_strdup(bs->env[i]);
		i++;
	}
	if (add_key)
	{
		new_array[i] = new_val;
		new_array[i + 1] = NULL;
		bs->n_env++;
	}
	else
		new_array[i] = NULL;
	free(bs->env);
	dup_array_to_env(bs, new_array);
}

void	dup_array_to_env(t_builtins *bs, char **array)
{
	int	i;

	bs->env = malloc (sizeof(char *) * bs->n_env);
	if (!bs->env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < bs->n_env)
	{
		bs->env[i] = array[i];
		i++;
	}
	bs->env[i] = NULL;
	free(array);
}
