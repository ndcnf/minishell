/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/25 17:19:09 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_builtins *bs, int argc, char *argv[])
{
	int	i;
	bs->args = malloc(sizeof(char *) * (argc + 1));
	
	// Stocker temporairement les argv entres dans une structure
	// et decaler afin de ne plus avoir le nom "./minishell" en premier
	// argument
	i = 0;
	while (i < (argc - 1))
	{
		bs->args[i] = argv[i + 1];
		//printf("b_init[%d]: %s\n", i, bs->args[i]);
		i++;
	}
	bs->n_args = i;
}

int	b_echo(t_builtins *bs)
{
	int	i;
	int	s_len;

	if (bs->n_args == 1)
		printf("\n");
	if (bs->n_args >= 2)
	{
		if (ft_strncmp(bs->args[1], "-n", strlen(bs->args[1])) == 0)
		{
			if (bs->n_args != 2)
			{
				i = bs->n_args - 1;
				while (i < bs->n_args)
				{
					printf("%s", bs->args[bs->n_args - i]);
					i--;
				}
			}
		}
		else
			printf("%s", bs->args[1]);
	}
	return (EXIT_SUCCESS);
}