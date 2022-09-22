/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/22 11:34:55 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_data *dt)
{
	char	dir[MAX_PATH];

	(void)dt;
	if (getcwd(dir, sizeof(dir)))
		ft_printf("%s\n", dir);
	//exit_stat = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////
int	b_exit(t_builtins *bs)
{
	printf("%s\n", bs->args[0]); //plus simple : "exit\n" mais evite dutiliser un (void)bs
	if (bs->n_args > 1)
		printf(ERR_ARG);
	exit(EXIT_SUCCESS);
}

// 'env'		-> affiche la liste des variables d'environnement
// 'env texte'	-> idem, rien de plus, rien de moins
/////////////////////////////////////////////////////////////////
int	b_env(t_data *dt)
{
	int	i;

	i = 0;
	while (i < dt->n_env)
		printf("%s\n", dt->env[i++]);
	return (EXIT_SUCCESS);
}
