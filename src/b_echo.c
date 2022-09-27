/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:42:21 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/27 11:37:35 by nchennaf         ###   ########.fr       */
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
				ft_printf("%s", dt->in[in].elem->cont[i]);
				i++;
				if (i != dt->in[in].n_elem)
					ft_printf(" ");
			}
			ft_printf("\n");
		}
	}
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

// DISPATCHE SELON LES CAS DANS LA BONNE FONCTION ET RETOURNERA LA BONNE STRING
char	*entrequotes(char *s, int j)
{
	// char	*new_str;
	// int		len;
	// int		i;

	// len = ft_strlen(s);
	// i = 0;
	// while (s[i])
	// {
	// 	if (s[i] == '\"')
	// 	{

	// 	}
	// 	i++;
	// }


	// new_str = malloc(sizeof(char) * len);
	// return (new_str);
}
