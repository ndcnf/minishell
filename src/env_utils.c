/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:44:46 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/10 15:21:37 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(char **elem)
{
	if (elem[1]) // A TESTER, SI AUCUNE VALEUR DONNEE POUR LA CLEF
		printf("declare -x %s=\"%s\"\n", elem[0], elem[1]);
	else if (elem[0])
		printf("declare -x %s\n", elem[0]);
}

char	**parse_env(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	return (elem);
}

//Separer en DUPLIQUER environnement et SORT environnement
void	sort_env(t_builtins *bs)
{
	int		i;
	int		j;
	char	*tempura;
	char	**export;

	export = malloc(sizeof(char *) * bs->n_env);
	malloc_checker((char *)export);
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
		print_env(parse_env(export[i++]));
}
