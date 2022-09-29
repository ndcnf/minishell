/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:29:31 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/29 09:30:46 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*quotes_ignorer(char *s)
{
	int		i;
	int		j;
	int		last;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	malloc_checker(new_s);
	i = 0;
	j = 0;
	last = ft_strlen(s) - 1;
	while (s[i])
	{
		if ((s[0] == '\'' || s[0] == '\"') && i == 0)
			i++;
		else if ((s[last] == '\'' || s[last] == '\"') && i == last)
			break ;
		else
			new_s[j++] = s[i++];
	}
	new_s[i] = '\0';
	// free(s);
	return (new_s);
}

int		trimquotes(t_data *dt, char *s, int in, int i)
{
	// int		i;
	char	*tempura;
	int		ret;

	ret = 0;
	// i = 0;
	// while (i < dt->in[in].n_elem)
	// {
	if (ft_strncmp(dt->in[in].elem->cont[i], s, ft_strlen(s)) == 0)
	{
		tempura = dt->in[in].elem->cont[i];
		dt->in[in].elem->cont[i] = ft_strtrim(dt->in[in].elem->cont[i], s);
		free(tempura);
		ret = 1;
	}
		// i++;
	// }
	return (ret);
}
