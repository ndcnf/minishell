/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exception_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:59:38 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 21:59:08 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_qts_split(char *s, int i, char c)
{
	if (s[i] == c && s[i + 1] == c)
		return (1);
	if (s[i] == c)
	{
		i++;
		while (s[i] != c)
		{
			if (!s[i])
				return (1);
			i++;
			if ((s[i] == c && s[i + 1] == ' ')
				|| (s[i] == c && s[i + 1] == '\0')
				|| (s[i] == c && s[i + 1] == '|'))
				return (i);
		}
	}
	return (i);
}
