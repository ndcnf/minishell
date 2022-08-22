/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:42:21 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/22 12:27:19 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			print_echo_n(bs, 2);
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
	i = 0;
	while (i < bs->n_args)
	{
		printf("FREE [%s], {%p}\n", bs->args[i], bs->args[i]);
		i++;
	}
	// i = 0;
	// while (i < bs->n_args)
	// 	free(bs->args[i++]);
	return (EXIT_SUCCESS);
}

void	print_echo_n(t_builtins *bs, int i)
{
	if (bs->n_args != 2)
	{
		while (i < bs->n_args)
		{
			printf("%s", bs->args[i]);
			i++;
			if (i != bs->n_args)
				printf(" ");
		}
	}
}
