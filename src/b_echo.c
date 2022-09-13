/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:42:21 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/13 10:32:57 by mthiesso         ###   ########.fr       */
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
int	b_echo(t_data *dt)
{
	(void) *dt;
	printf("JE SUIS ECHO\n");
	// int	i;

	// if (in->n_elem < 4)
	// 	printf("\n");
	// if (in->n_elem >= 3)
	// {
	// 	//skip_quotes(in, 3); //faut-il donner un index a input pour lui dire dans lequel on veut les infos ? Need HELP
	// 	if (ft_strncmp(in->elem->cont[3], "-n", strlen(in->elem->cont[3])) == 0)
	// 		print_echo_n(in, 2);
	// 	else if (ft_strncmp(in->elem->cont[4], "-n", \
	// 		strlen(in->elem->cont[4])) == 0)
	// 		print_echo_n(in, 2);
	// 	else
	// 	{
	// 		i = 1;
	// 		while (i < bs->n_args)
	// 		{
	// 			printf("%s", bs->args[i]);
	// 			i++;
	// 			if (i != bs->n_args)
	// 				printf(" ");
	// 		}
	// 		printf("\n");
	// 	}
	// i = 0;
	// while (i < bs->n_args)
	// {
	// 	printf("FREE [%s], {%p}\n", bs->args[i], bs->args[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < bs->n_args)
	// 	free(bs->args[i++]);
	return (EXIT_SUCCESS);
}

// void	print_echo_n(t_builtins *bs, int i)
// {
// 	if (bs->n_args != 2) //in->n_elem
// 	{
// 		while (i < bs->n_args)
// 		{
// 			printf("%s", bs->args[i]);
// 			i++;
// 			if (i != bs->n_args)
// 				printf(" ");
// 		}
// 	}
// }
