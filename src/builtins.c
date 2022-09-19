/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/19 11:05:25 by nchennaf         ###   ########.fr       */
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

	if (getcwd(dir, sizeof(dir)) == NULL)
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

int	b_cd(t_data *dt, int in)
{
	char	dir[MAX_PATH];
	// char	**tempura;
	int		i;
	(void)in;

	// tempura = malloc(sizeof(char *) * dt->n_env);
	// malloc_checker((char *)tempura);

	i = 0;
	while (ft_strncmp(parse_env(dt->env[i])[0], "OLDPWD", 6) && i < dt->n_env)
		i++;

	ft_printf("[%s]\n", dt->env[i]);
	// ft_printf("env[%d]: [%s] [%s]\n", i, parse_env(dt->env[i])[0], parse_env(dt->env[i])[1]);
	dt->env[i] = ft_strjoin("OLDPWD=", parse_env(dt->env[i])[1]);
	ft_printf("[%s]\n", dt->env[i]);




	// while (dt->env[i] != ft_strncmp(dt->env[i], "OLDPWD", ft_strlen(dt->env[i])))
	// 	i++;
	// dt->env[i] = ft_strdup(getcwd(dir, MAX_PATH));

	// if (dt->in[in].n_elem == 1) //S'il n''y a QUE 'cd', sans flag, ni arg
	// {
	// 	if (chdir(getenv("HOME")) != 0)
	// 	{
	// 		perror("ERR");
	// 		return (EXIT_FAILURE);
	// 	}
	// }
	// else if (chdir(dt->in[in]->elem) != 0)
	if (chdir("..") != 0)
	{
		perror("ERR");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (ft_strncmp(parse_env(dt->env[i])[0], "PWD", 3))
		i++;
	ft_printf("avant : [%s]\n", dt->env[i]); // UNIQUEMENT POUR VERIFICATION, A SUPPRIMER
	dt->env[i] = ft_strjoin("PWD=", getcwd(dir, MAX_PATH));
	ft_printf("apres : [%s]\n", dt->env[i]); // UNIQUEMENT POUR VERIFICATION, A SUPPRIMER
	return (EXIT_SUCCESS);
}

// int

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////
int	b_exit(t_builtins *bs)
{
	printf("%s\n", bs->args[0]); //plus simple : "exit\n" mais evite dutiliser un (void)bs
	if (bs->n_args > 1)
		printf("argument isn't valid in this program\n");
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
