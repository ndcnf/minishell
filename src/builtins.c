/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/08 13:28:06 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[])
{
	int	i;

	bs->args = malloc(sizeof(char *) * (argc + 1));
	if (!bs->args)
		exit(EXIT_FAILURE);
	// Stocker temporairement les argv entres dans une structure
	// et decaler afin de ne plus avoir le nom "./minishell" en premier
	// argument

	i = 0;
	while (envp[i] != NULL)
		i++;
	bs->n_env = i;
	bs->env = malloc(sizeof(char *) * bs->n_env);
	if (!bs->env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < bs->n_env)
	{
		bs->env[i] = ft_strdup(envp[i]);
		// printf("[%s]\n", bs->env[i]);
		i++;
	}
	i = 0;
	while (i < (argc - 1))
	{
		bs->args[i] = argv[i + 1];
		//printf("b_init[%d]: %s\n", i, bs->args[i]);
		i++;
	}
	bs->n_args = i;
}

// 'echo'				-> retour à la ligne
// 'echo -n'			-> rien, ligne suivante
// 'echo -n texte'		-> 'texte'
// 'echo texte'			-> 'texte\n'
// 'echo texte long'	-> 'texte long\n'
// 'echo -n texte long'	-> 'texte long'
// 'echo texte -n'		-> 'texte -n\n'
///////////////////////////////////////////////
int	b_echo(t_builtins *bs)
{
	int	i;

	if (bs->n_args == 1)
		printf("\n");
	if (bs->n_args >= 2)
	{
		if (ft_strncmp(bs->args[1], "-n", strlen(bs->args[1])) == 0)
		{
			if (bs->n_args != 2)
			{
				i = 2;
				while (i < bs->n_args)
				{
					printf("%s", bs->args[i]);
					i++;
					if (i != bs->n_args)
						printf(" ");
				}
			}
		}
		else
		{
			i = 1;
			while (i < bs->n_args)
			{
				printf("%s", bs->args[i]);
				i++;
				if (i != bs->n_args)
					printf(" ");
			}
			printf("\n");
		}
	}
	return (EXIT_SUCCESS);
}
// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_builtins *bs)
{
	char	dir[MAX_PATH];

	if (bs->n_args > 1)
	{
		printf("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("pwd");
	else
		printf("%s\n", dir);
	return (EXIT_SUCCESS);
}

// 'cd ~'		-> retour a /Users/(nom du user)
// 'cd'			-> identique a 'cd ~'
// 'cd ..'		-> retour un niveau avant (le prompt l'affiche)
// 'cd .'		-> on reste et fait rien
// 'cd (dir)'	-> on va dans le dossier (dir)
/////////////////////////////////////////////////////////////////////
int	b_cd(t_builtins *bs)
{
	char	dir[MAX_PATH];

	bs->path = getcwd(dir, MAX_PATH);
	if (bs->n_args == 1)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("ERR");
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(bs->args[1]) != 0)
	{
		perror("ERR");
		return (EXIT_FAILURE);
	}
	bs->path = getcwd(dir, MAX_PATH);
	printf("PATH : [%s]\n", bs->path); // UNIQUEMENT POUR VERIFICATION, A SUPPRIMER
	return (EXIT_SUCCESS);
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
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
int	b_env(t_builtins *bs)
{
	int	i;

	i = 0;
	while (i < bs->n_env)
	{
		printf("%s\n", bs->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

// 'export'				-> affiche liste des variables environnement, triees par ASCII
// 'export bonjour'		-> cree la variable bonjour seule, rien ne s'affiche. Cette info ne sera pas ajoutee lors de l'affichage de env, mais dans export oui
// 'export test=texte	-> cree la variable test="texte", rien ne s'affiche. Cette info sera ajoutee lors de l'affichage de env et export
//////////////////////////////////////////////////////////////////////////////////////
int	b_export(t_builtins *bs)
{
	if (bs->n_args == 1)
	{
		sort_env(bs);
	}
	else
		printf("creer une nouvelle variable\n");
	// declare -x VARIABLE="valeur"\n
	// option=truc, ajouter dans les variables et mettre a jour le nombre de variables
	return (EXIT_SUCCESS);
}

void	parse_env(t_builtins *bs)
{
	int		i;
	char	***env_elements;

	env_elements = malloc(sizeof(char **) * bs->n_env);
	if (!env_elements)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < bs->n_env)
	{
		env_elements[i] = ft_split(bs->env[i], '=');
		printf("variable[%s]\n", env_elements[i][0]);
		printf("valeur[%s]\n", env_elements[i][1]);
		i++;
	}
}

// void	print_export(char *s)
// {

// }

void	sort_env(t_builtins *bs)
{
	int		i;
	int		j;
	char	*tempura;
	char	**export;

	export = malloc(sizeof(char *) * bs->n_env);
	if(!export)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < bs->n_env)
	{
		export[i] = ft_strdup(bs->env[i]);
		i++;
	}
	i = 0;
	while (i < bs->n_env)
	{
		j = i + 1;
		while (j < bs->n_env)
		{
			if (ft_strncmp(export[j], export[i], MAX_PATH) < 0)
			{
				tempura = export[i];
				export[i] = export[j];
				export[j] = tempura;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < bs->n_env)
	{
		printf("declare -x %s\n", export[i]); //le printf devra inclure " " plus tard, spliter avec '=' ?
		i++;
	}
}
