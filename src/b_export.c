/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:48:36 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/10 12:20:46 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 'export'				-> affiche liste des variables environnement, triees par ASCII
// 'export bonjour'		-> cree la variable bonjour seule, rien ne s'affiche. Cette info ne sera pas ajoutee lors de l'affichage de env, mais dans export oui
// 'export test=texte	-> cree la variable test="texte", rien ne s'affiche. Cette info sera ajoutee lors de l'affichage de env et export
//////////////////////////////////////////////////////////////////////////////////////
int	b_export(t_builtins *bs)
{
	int	i;

	if (bs->n_args == 1)
		sort_env(bs);
	else
	{
		i = 1;
		while (i < bs->n_args)
			add_key(bs, i++);
		sort_env(bs); //VERIFICATION UNIQUEMENT
	}
	return (EXIT_SUCCESS);
}

// char	*key_checker(t_builtins *bs, char **elem)
// {

// }

// Cette fonction contient des leaks
void	add_key(t_builtins *bs, int pos)
{
	char	*new_key;
	char	*new_val;
	// char	*check;
	int		i;

	new_key = malloc(sizeof(char) * ft_strlen(bs->args[pos]));
	malloc_checker(new_key);
	// check = malloc (sizeof(char *) * ft_strlen(bs->args[pos]));
	// check = malloc(sizeof(char) * ft_strlen(parse_env(bs->args[pos])));
	// malloc_checker(check);
	i = 0;
	new_val = ft_strchr(bs->args[pos], '=');
	while (bs->args[pos][i] != '=')
	{
		new_key[i] = bs->args[pos][i];
		i++;
	}
	new_key[i] = '\0';
	// check = malloc (sizeof(char *) * ft_strlen(parse_env(bs->args[pos])));
    // check = key_checker(bs, parse_env(bs->args[pos]));
	need_bigger_array(bs, new_key, new_val);
	// if (new_key)
	// 	free(new_key);
}

void	need_bigger_array(t_builtins *bs, char *key, char *val)
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
	bs->n_env++;
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
