/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:23:52 by marlene           #+#    #+#             */
/*   Updated: 2022/09/07 13:09:48 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_init(char *args, t_input *input)
{
	int			i;

	i = 0;
	input = malloc(sizeof(t_input));
	input->elem = malloc(sizeof(t_elem));
	input->nb_cmd = 1;
	while (args[i])
	{
		if (args[i] == '|')
			input->nb_cmd++;
		i++;
	}
	input->content = ft_split(args, '|');
	i = 0;
	while (i < input->nb_cmd)
	{
		input->nb_elem = 1;
		input->content[i] = parse_cmd(input, input->content[i]);
		space_counter(input, input->content[i++]);
		printf("%d\n", input->nb_elem);
		input->elem->content = malloc(sizeof(char *) * input->nb_elem);
	}
}

char	*parse_cmd(t_input *input, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_quotes(input, s) == 1)
		printf("DEGAGE\n");
	s = ft_strtrim(s, " ");
	return (s);
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
