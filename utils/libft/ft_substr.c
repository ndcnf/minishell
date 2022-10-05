/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:06:11 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 18:05:23 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t end)
{
	char		*substr;
	size_t		counter;
	size_t		size;

	size = end - start + 1;
	substr = (char *) malloc(sizeof(char) * (size + 1));
	malloc_checker(substr);
	counter = 0;
	while (start <= end && s[start] != '\0')
	{
		substr[counter] = s[start];
		counter++;
		start++;
	}
	substr[counter] = '\0';
	return (substr);
}
