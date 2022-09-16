/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:36:59 by mthiesso          #+#    #+#             */
/*   Updated: 2022/09/16 13:53:57 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Example:
 * s1        "....,.,,..,,,.,Hell,,.,.,o.,.,.,,.,."
 * set        ".,"
 * return:    "Hell,,.,.,o"
 * ____________________________________________________*/
 
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!set || !s1)
		return (NULL);
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (j > i && ft_strchr(set, s1[j]) != NULL)
		j--;
	tmp = ft_substr((char *)(s1 + i), 0, (j - i));
	return (tmp);
}
