/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/08/29 14:41:56 by marlene          ###   ########.fr       */
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
    
    in = malloc(sizeof(char *) + 1);
    in = bs->content;
    if (parse_pwd(bs, in) == 1)
            b_pwd(bs);
}

int    parse_pwd(t_builtins *bs, char *in)
{
    int i;
    bs->len = ft_strlen(in);
    i = 0;
    in = ft_strtrim(in, " ");
    while (in[i])
    {
        if (ft_strncmp(in, "pwd", 3) == 0)
            return(1);
        i++;
    }
    return(0);
}