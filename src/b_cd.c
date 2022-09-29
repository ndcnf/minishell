/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:07:43 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/29 13:26:09 by nchennaf         ###   ########.fr       */
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
			return (print_cd(ERR_NO_ARG, 1)); //---------------------------------EXIT NUMBER TO DEFINE HERE
		if (chdir(dt->in[in].elem->cont[n]))
		{
			perror("ERR");
			return (EXIT_FAILURE);
		}
	}
	update_env(dt, dir);
	return (EXIT_SUCCESS);
}

void	update_env(t_data *dt, char *dir)
{
	int	i;
	int	j;

	i = where_in_env(dt, "PWD", 3);
	j = where_in_env(dt, "OLDPWD", 6);
	if (i == NO_RESULT)
		ft_printf(CMD_404);
	else
	{
		dt->env[j] = ft_strjoin("OLDPWD", parse_env(dt->env[i])[1]);
		dt->env[i] = ft_strjoin("PWD=", getcwd(dir, MAX_PATH));
	}
}

int	where_in_env(t_data *dt, char *key, int len)
{
	int	i;

	i = 0;
	// while (ft_strncmp(parse_env(dt->env[i])[0], key, len) && i < dt->n_env)
	// 	i++;
	while (i < dt->n_env)
	{
		if (ft_strncmp(dt->env[i], key, len) == 0)
			return (i);
		i++;
	}
	// if (i > dt->n_env)
	// 	return (-1);
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

	i = where_in_env(dt, "HOME", 5);
	if (i == NO_RESULT)
	{
		ft_printf(HOMELESS);
		return (EXIT_FAILURE);
	}
	else if (chdir(parse_env(dt->env[i])[1]))
	{
		perror("ERR");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
