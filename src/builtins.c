/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/30 14:44:23 by nchennaf         ###   ########.fr       */
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
	return (the_end(NULL, EXIT_SUCCESS));
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////
int	b_exit(t_data *dt, int in)
{
	int	n;

	n = 0;
	if (dt->in[in].n_elem > 2)
		return (the_end(TM_ARG, EXIT_FAILURE));
	else if (dt->in[in].n_elem == 1)
	{
		ft_printf("exit\n");
		exit(the_end(NULL, EXIT_SUCCESS));
	}
	else if (dt->in[in].n_elem == 2)
	{
		n = ft_atoi(dt->in[in].elem->cont[1]);
		exit (the_end("exit\n", n));
	}


	// else if (dt->in[in].n_elem == 2)
	//g_exit_stat = ft_atoi(dt->in[in].elem->cont[1]); // assigner la valeur donee dans la variable globale
	// else
	// 	g_exit_stat = EXIT_SUCCESS;
	exit(the_end(NULL, EXIT_SUCCESS)); //remplacer par la variable globale plus tard
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
