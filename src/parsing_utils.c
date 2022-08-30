/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:36:28 by marlene           #+#    #+#             */
/*   Updated: 2022/08/18 22:18:26 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    skip_spaces(t_builtins *bs, char *in)
{
    int i;

    i = 0;
    while (in[i])
    {
        if (in[i] != ' ')
        {
            bs->len = ft_strlen(in) - i;
            return (1);
        }
        i++;
    }
    return (0);
}