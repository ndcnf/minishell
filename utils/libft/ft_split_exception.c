/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exception.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:44:45 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 20:13:25 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Example:
 * s		"Everything needs a delimiter."
 * c		" "
 * return	"Everything", "needs", "a", "delimiter.", NULL
 * ------------------------------------------------------------*/

/* This function returns the number of words (strings) in
the string s */

int	is_quotes(char *s, int i) // -------------------------------------------------- FAUDRA REPARER POUR ACCEPTER LES QUOTES CONSECUTIVES (sinon compte comme "uneven")
{
	int	j;

	j = i;
	while (s[i])
	{
		if (s[i] == '\"' && s[i + 1] == '\"')
		{
			return (1);
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				if (!s[i])
					return (1);
				i++;
				if ((s[i] == '\"' && s[i + 1] == ' ')
					|| (s[i] == '\"' && s[i + 1] == '\0')
					|| (s[i] == '\"' && s[i + 1] == '|'))
					return (i);
			}
		}
		else if (s[i] == '\'' && s[i + 1] == '\'')
			return (1);
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			{
				if (!s[i])
					return (NO_RESULT);
				i++;
				if ((s[i] == '\'' && s[i + 1] == ' ')
					|| (s[i] == '\'' && s[i + 1] == '\0')
					|| (s[i] == '\'' && s[i + 1] == '|'))
					return (i);
			}
		}
		i++;
	}
	return (j);
}

static int	word_cnt(char *s, char c)
{
	int	i;
	int	is_word;
	int	cnt;

	i = 0;
	is_word = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = is_quotes(s, i);
		if (s[i] == c)
			is_word = 0;
		else if (s[i] != c && is_word == 0)
		{
			is_word = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

/* This function retrieves the string without any delimiter.
It will be used with pointers with the function ft_split to
know where every word begins and ends. */

static char	*words_without_borders(char *s, char c)
{
	int		i;
	int		w_len;
	char	*ptr;

	i = 0;
	w_len = 0;
	while (s[w_len] && s[w_len] != c)
	{
		if (s[w_len] == '\"' || s[w_len] == '\'')
			w_len = is_quotes(s, w_len);
		if (s[w_len] != c)
			w_len++;
	}
	ptr = (char *)ft_calloc((w_len + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < w_len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* This function will detect every valid delimiter and truncate
the string. Pointers will then know where every word begins. */

static void	*new_str(char *s, char c, int w_cnt, int toggle)
{
	int	i;
	int	p;

	i = 0;
	while (s[i])
	{
		if (s[0] != c && toggle == 0)
			return ((char *)&s[0]);
		if (s[i - 1] != c && (s[i] == '\"' || s[i] == '\''))
			i = is_quotes(s, i);
		p = i - 1;
		if ((s[i] != c && i > 0 && s[p] == c) || (w_cnt == 0 && s[i] != c))
			return ((char *)&s[i]);
		i++;
	}
	return ((char *)s);
}

char	**ft_split_ex(char const *s, char c)
{
	int		i;
	char	**lean;
	int		w_cnt;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	w_cnt = word_cnt(str, c);
	lean = (char **)ft_calloc(sizeof(char *), (w_cnt + 1));
	if (lean == NULL)
		return (NULL);
	while (i < w_cnt)
	{
		str = new_str(str, c, w_cnt, i);
		lean[i] = words_without_borders(str, c);
		if (lean[i] == NULL)
			return (NULL);
		i++;
	}
	lean[i] = NULL;
	return (lean);
}
