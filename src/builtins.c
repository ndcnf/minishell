/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 11:10:47 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_data *dt)
{
	char	dir[MAX_PATH];

	(void)dt;
	if (getcwd(dir, sizeof(dir)))
		ft_printf("%s\n", dir);
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////
int	b_exit(t_data *dt, int in)
{
	int	n;

	if (dt->in[in].n_elem == 1)
	{
		ft_printf("exit\n");
		exit (the_end(NULL, g_exit_stat, 0));
	}
	if (dt->in[in].n_elem > 2)
	{
		if (ft_atoi(dt->in[in].elem->cont[1])
			|| dt->in[in].elem->cont[1][0] == '0')
			return (the_end(TM_ARG, EXIT_FAILURE, 1));
		exit (the_end(NOT_NUM, ERR_EXIT, 1));
	}
	n = ft_atoi(dt->in[in].elem->cont[1]);
	if (n || dt->in[in].elem->cont[1][0] == '0')
		exit (the_end("exit\n", n, 0));
	exit (the_end(NOT_NUM, ERR_EXIT, 1));
}

// 'env'		-> affiche la liste des variables d'environnement
// 'env texte'	-> idem, rien de plus, rien de moins
/////////////////////////////////////////////////////////////////
int	b_env(t_data *dt)
{
	int	i;

	i = 0;
	while (i < dt->n_env)
	{
		if (ft_strchr(dt->env[i], '='))
			ft_printf("%s\n", dt->env[i]);
		i++;
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}
