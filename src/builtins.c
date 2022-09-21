/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/21 12:04:59 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_data *dt)
{
	(void)dt;
	char	dir[MAX_PATH];

	if (getcwd(dir, sizeof(dir)))
		ft_printf("%s\n", dir);
	//exit_stat = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

// 'cd ~'		-> retour a /Users/(nom du user)
// 'cd'			-> identique a 'cd ~'
// 'cd ..'		-> retour un niveau avant (le prompt l'affiche)
// 'cd .'		-> on reste et fait rien
// 'cd (dir)'	-> on va dans le dossier (dir)
/////////////////////////////////////////////////////////////////////
// int	b_cd(t_data *dt, int in)
// {
// 	char	dir[MAX_PATH];
// 	int		i;

// 	i = 0;
// 	while (dt->env[i] != ft_strncmp(dt->env[i], "OLDPWD", ft_strlen(dt->env[i])))
// 		i++;
// 	dt->env[i] = ft_strdup(getcwd(dir, MAX_PATH));

// 	if (dt->in[in].n_elem == 1) //S'il n''y a QUE 'cd', sans flag, ni arg
// 	{
// 		if (chdir(getenv("HOME")) != 0)
// 		{
// 			perror("ERR");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	// else if (chdir(bs->args[1]) != 0)
// 	// {
// 	// 	perror("ERR");
// 	// 	return (EXIT_FAILURE);
// 	// }
// 	dt->path = getcwd(dir, MAX_PATH);
// 	printf("PATH : [%s]\n", dt->path); // UNIQUEMENT POUR VERIFICATION, A SUPPRIMER
// 	return (EXIT_SUCCESS);
// }

int	where_in_env(t_data *dt, char *key, int len)
{
	int	i;

	i = 0;
	while (ft_strncmp(parse_env(dt->env[i])[0], key, len) && i < dt->n_env)
		i++;
	return (i);
}

int	b_cd(t_data *dt, int in)
{
	char	dir[MAX_PATH];
	int		i;
	int		j;
	int		n;

	i = where_in_env(dt, "HOME", 4);
	if (dt->in[in].n_elem == 1)
	{
		if (chdir(parse_env(dt->env[i])[1]))
		{
			perror("ERR");
			return (EXIT_FAILURE);
		}
		n = 0;
	}
	else
		n = 1;
	if (n)
	{
		if (dt->in[in].elem->cont[n][0] == '-') // <-----------------------------------PROBLEME ICI avec 'cd' seul, mais fonctionne pour detecter les options
		{
			ft_printf(OPT_IGN);
			n = 2;
		}
		if (n >= dt->in[in].n_elem)
		{
			ft_printf(ERR_NO_ARG);
			return (EXIT_FAILURE);
		}
		if (chdir(dt->in[in].elem->cont[n]))
		{
			perror("ERR");
			return (EXIT_FAILURE);
		}
	}
	i = where_in_env(dt, "PWD", 3);
	j = where_in_env(dt, "OLDPWD", 6);
	dt->env[j] = ft_strjoin("OLDPWD", parse_env(dt->env[i])[1]);
	dt->env[i] = ft_strjoin("PWD=", getcwd(dir, MAX_PATH));
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
