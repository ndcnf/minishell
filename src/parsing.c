/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/05 14:29:54 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_init(char *args, t_input *input)
{
	int			i;

	i = 0;
	input = malloc(sizeof(t_input));
	input->nb_cmd = 1;
	while (args[i])
	{
		if (args[i] == '|')
			input->nb_cmd++;
		i++;
	}
	ft_printf("nb_cmd : %d\n", input->nb_cmd);
	input->content = ft_split(args, '|');
	i = 0;
	while (i < input->nb_cmd)
	{
		parse_cmd(input->content[i]);
		ft_printf("content: %s\n", input->content[i]);
		i++;
	}
	//dividing_args(&bs);
}

void	parse_cmd(char *s)
{
	int	i;

	i = 0;
	if (check_quotes(s) == 1)
		printf("DEGAGE\n");
	while (s[i])
	{
		// if (check_quotes(s) == 1)
		// {
		// 	printf("DEGAGE\n");
		// 	break ;
		// }
		i++;
	}
}
void	dividing_args(t_builtins *bs)
{
	char	*in;

	in = malloc(sizeof(char *) + 1);
	in = bs->content;
	if (parse_pwd(bs, in) == 1)
		b_pwd(bs);
}

int	parse_pwd(t_builtins *bs, char *in)
{
	int	i;

	bs->len = ft_strlen(in);
	i = 0;
	in = ft_strtrim(in, " ");
	while (in[i])
	{
		if (ft_strncmp(in, "pwd", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}
