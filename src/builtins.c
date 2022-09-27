/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/27 13:48:14 by nchennaf         ###   ########.fr       */
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
	// g_exit_stat = EXIT_SUCCESS;
	// return (g_exit_stat);
	return (EXIT_SUCCESS);
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////
int	b_exit(t_data *dt, int in)
{
	ft_printf("exit\n");
	if (dt->in[in].n_elem > 2)
	{
		ft_printf(TM_ARG);
		// g_exit_stat = EXIT_FAILURE; // assigner la valeur donee dans la variable globale
	}
	// else if (dt->in[in].n_elem == 2)
	// 	g_exit_stat = ft_atoi(dt->in[in].elem->cont[1]); // assigner la valeur donee dans la variable globale
	// else
	// 	g_exit_stat = EXIT_SUCCESS;
	exit(EXIT_SUCCESS); //remplacer par la variable globale plus tard
	// exit(g_exit_status);
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
	return (EXIT_SUCCESS);
}
