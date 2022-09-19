/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:42:21 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/13 19:09:45 by mthiesso         ###   ########.fr       */
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
int	b_echo(t_data *dt, int in)
{
	int	i;

	i = 0;
	if (dt->in[in].n_elem < 4)
		ft_printf("\n");
	if (dt->in[in].n_elem > 3)
	{
		i = skip_quotes(&dt->in[in], 3);
		if (ft_strncmp(dt->in[in].elem->cont[i], "-n", 2) == 0)
			print_echo_n(&dt->in[in], i);
		else
		{
			while (i < dt->in[in].n_elem)
			{
				i = skip_quotes(&dt->in[in], i);
				if (i == dt->in[in].n_elem)
					break ;
				ft_printf("[%s]", dt->in[in].elem->cont[i]);
				i++;
				i = skip_quotes(&dt->in[in], i);
				if (i < dt->in[in].n_elem)
					ft_printf("[H]");
			}
			ft_printf("\n");
		}
	}
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

void	print_echo_n(t_input *in, int i)
{
	i = skip_quotes(in, i);
	i = skip_n(in, i);
	while (i < in->n_elem)
	{
		i = skip_quotes(in, i);
		if (ft_strncmp(in->elem->cont[i], "\0", 1))
		{
			ft_printf("%s", in->elem->cont[i]);
			if (i != in->n_elem - 1)
				ft_printf(" ");
			i++;
		}
		i = skip_quotes(in, i);
	}
}

// void	print_echo_quotes(t_input *in, int i)
// {
// 	while (i < in->n_elem)
// 	{
// 		i = skip_quotes(in, i);
// 		if (i == in->n_elem)
// 			break ;
// 		ft_printf("[%s]", in->elem->cont[i]);
// 		i++;
// 		if (i != in->n_elem - 1)
// 			ft_printf("[ ]");
// 	}
// }
