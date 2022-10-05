/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:07:43 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 21:21:28 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 'cd ~'		-> retour a /Users/(nom du user)
// 'cd'			-> identique a 'cd ~'
// 'cd ..'		-> retour un niveau avant (le prompt l'affiche)
// 'cd .'		-> on reste et fait rien
// 'cd (dir)'	-> on va dans le dossier (dir)
// BIEN PROTEGER EN AMONT :
//			[] si autre chose que 'cd'
//			[] si aucun argument entré (rien dans le prompt)
/////////////////////////////////////////////////////////////////////
int	b_cd(t_data *dt, int in)
{
	char	dir[MAX_PATH];
	int		n;

	if (dt->in[in].n_elem == 1)
	{
		no_place_like_home(dt);
		n = 0;
	}
	else
		n = 1;
	if (n)
	{
		if (dt->in[in].elem->cont[n][0] == '-')
			n = print_cd(OPT_IGN, 2);
		if (n >= dt->in[in].n_elem)
			return (the_end(ERR_NO_ARG, EXIT_FAILURE, 1));
		if (chdir(dt->in[in].elem->cont[n]))
			return (the_end(ERROR, EXIT_FAILURE, 1));
	}
	update_env(dt, dir);
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	update_env(t_data *dt, char *dir)
{
	int		i;
	int		j;
	char	**splited;

	i = where_in_env(dt, "PWD", 3);
	j = where_in_env(dt, "OLDPWD", 6);
	if (i == NO_RESULT)
		ft_printf(CMD_404);
	else
	{
		free(dt->env[j]);
		splited = parse_env(dt->env[i]);
		dt->env[j] = ft_strjoin("OLDPWD=", splited[1]);
		freearray(splited, 2);
		free(dt->env[i]);
		dt->env[i] = ft_strjoin("PWD=", getcwd(dir, MAX_PATH));
	}
}

int	where_in_env(t_data *dt, char *key, int len)
{
	int	i;
	int	diff;

	i = 0;
	while (i < dt->n_env)
	{
		diff = ft_strncmp(dt->env[i], key, len + 1);
		if (diff == 0 || diff == 61)
			return (i);
		i++;
	}
	return (NO_RESULT);
}

int	print_cd(char *s, int n)
{
	ft_printf(s);
	return (n);
}

int	no_place_like_home(t_data *dt)
{
	int		i;
	char	**tempura;

	i = where_in_env(dt, "HOME", 5);
	if (i == NO_RESULT)
		the_end(HOMELESS, EXIT_FAILURE, 1);
	else
	{
		tempura = parse_env(dt->env[i]);
		if (chdir(tempura[1]))
			the_end(ERROR, EXIT_FAILURE, 1);
		freearray(tempura, 2);
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}
