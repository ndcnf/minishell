/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/24 17:28:36 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(t_builtins *bs)
{
	if (strcmp(bs->args[1], "-n") == 0) //ajouter la fonction ft_strncmp pour comparer les strings
		printf("%s\n", bs->args[2]);
	printf("%s\n", bs->args[1]);

	return (EXIT_SUCCESS);
}