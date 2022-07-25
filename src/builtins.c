/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:40:41 by nchennaf          #+#    #+#             */
/*   Updated: 2022/07/25 15:36:57 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_builtins *bs, int argc, char *argv[])
{
	int	i;
	bs->args = malloc(sizeof(char *) * (argc + 1));
	
	i = 0;
	while (i < argc)
	{
		bs->args[i] = argv[i];
		//printf("binit: %s\n", bs->args[i]);
		i++;
	}
}

int	b_echo(t_builtins *bs)
{
	if (ft_strncmp(bs->args[2], "-n", ft_strlen(bs->args[2])) == 0)
		printf("%s\n", bs->args[3]);
	else
		printf("%s", bs->args[2]);

	return (EXIT_SUCCESS);
}