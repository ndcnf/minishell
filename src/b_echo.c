/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:42:21 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/01 12:50:46 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;

	if (dt->in[in].n_elem == 1)
		ft_printf("\n");
	if (dt->in[in].n_elem > 1)
	{
		i = 1;
		if (ft_strncmp(dt->in[in].elem->cont[i], "-n", 2) == 0)
			print_echo_n(&dt->in[in], i);
		else
		{
			while (i < dt->in[in].n_elem)
			{
				ft_printf("%s", dt->in[in].elem->cont[i++]);
				if (i != dt->in[in].n_elem)
					ft_printf(" ");
			}
			ft_printf("\n");
		}
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	print_echo_n(t_input *in, int i)
{
	i = skip_n(in, i);
	while (i < in->n_elem)
	{
		if (ft_strncmp(in->elem->cont[i], "\0", 1))
		{
			ft_printf("%s", in->elem->cont[i]);
			if (i != in->n_elem - 1)
				ft_printf(" ");
			i++;
		}
	}
}
