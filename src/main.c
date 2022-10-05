/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:47 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 18:35:13 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)envp;
	if (argc > 1)
	{
		ft_printf("\033[31mARG_ERROR\n\033[31m");
		return (1);
	}
	if (envp)
	{
		prompt(envp);
	}
}
