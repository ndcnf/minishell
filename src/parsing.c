/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/08/12 17:29:17 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parsing_init(char *args, t_input *input)
{
    t_builtins  bs;

    input = malloc(sizeof(t_input));
    input->content = args;
    bs.content = ft_strdup(input->content);
    dividing_args(&bs);
}

void    dividing_args(t_builtins *bs)
{
    char        *in;
    
    in = bs->content;
    if (parse_cmd(in) == 1)
            b_pwd(bs);
}

int    parse_cmd(char *in)
{
    if (ft_strncmp(in, "pwd", 3) == 0)
		return(1);
    return(0);
}