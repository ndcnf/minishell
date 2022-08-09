/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/09 15:04:41 by nchennaf         ###   ########.fr       */
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
		i++;
	}
	i = 0;
	while (i < (argc - 1))
	{
		bs->args[i] = argv[i + 1];
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
	int	i;
	printf("n_args[%d]\n", bs->n_args);
	if (bs->n_args == 1)
		sort_env(bs);
	else
	{
		i = 1;
		while (i < bs->n_args)
		{
			add_key(bs, i);
			i++;
		}
		sort_env(bs); //juste verif
	}
	return (EXIT_SUCCESS);
}

// void	parse_env(t_builtins *bs)
// {
// 	int		i;
// 	//char	***env_elem;

// 	bs->env_elem = malloc(sizeof(char **) * bs->n_env);
// 	if (!bs->env_elem)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (i < bs->n_env)
// 	{
// 		bs->env_elem[i] = ft_split(bs->env[i], '=');
// 		printf("%s = \"%s\"\n", bs->env_elem[i][0], bs->env_elem[i][1]);
// 		i++;
// 	}
// }

char	**parse_env(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	//if (elem)
		return (elem);
	///return (EXIT_FAILURE); //REPRENDRE ICI
}

void	parse_it(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	if (elem[1]) // A TESTER, SI AUCUNE VALEUR DONNEE POUR LA CLEF
		printf("declare -x %s=\"%s\"\n", elem[0], elem[1]);
	else
		printf("declare -x %s\n", elem[0]);
}

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
		// if (parse_env(export[i])[1])
		// 	printf("declare -x %s=\"%s\"\n", elem[0], elem[1]);
		// else
		// 	printf("declare -x %s\n", elem[0]);
		parse_it(export[i++]);
	}
}

// export chien de paille=ok -->
// declare -x chien
// declare -x de
// declare -x paille="ok"
// Pour l'ajout, ce sera une clef apres l'autre
void	add_key(t_builtins *bs, int pos)
{
	char	*new_key;
	char	*new_val;
	int		i;

	new_key = malloc(sizeof(char) * ft_strlen(bs->args[pos]));
	if (!new_key)
		exit(EXIT_FAILURE);
	new_val = malloc(sizeof(char) * ft_strlen(bs->args[pos]));
	if (!new_val)
		exit(EXIT_FAILURE);
	i = 0;
	new_val = ft_strchr(bs->args[pos], '=') + 1;

	////////////////////////////////////////////////////
	// Partie verification si aucune valeur a faire ici

	if (new_val != NULL)
		printf("%s\n", new_val); //UNIQUEMENT VERIF
	else
		printf("pas de valeur\n");
	//if (ft_strlen(new_val) == ft_strlen(bs->args[1]))
	////////////////////////////////////////////////////

	while (bs->args[pos][i] != '=')
	{
		new_key[i] = bs->args[pos][i];
		i++;
	}
	new_key[i] = '\0';
	need_bigger_array(bs, new_key, new_val);
	// if (new_key)
	// 	free(new_key);
	// if (new_val)
	// 	free(new_val);
}

void	need_bigger_array(t_builtins *bs, char *key, char *val)
{
	char	**new_array;
	char	*new_val;
	int		i;

	printf("n_env = [%d]\n", bs->n_env);
	new_array = malloc(sizeof(char *) * (bs->n_env + 1));
	if (!new_array)
		exit(EXIT_FAILURE);
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
