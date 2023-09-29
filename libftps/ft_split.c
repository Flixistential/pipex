/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:35:39 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:53:33 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[0] != c)
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	*word_maker(char const *s, size_t len)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = *s;
		s++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**splitter(char **split, const char *s, char c, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	j = 0;
	index = -1;
	while (++index < count)
	{
		while (s[i])
		{
			while (s[i] == c)
				i++;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			split[index] = word_maker(&s[i], (j));
			if (!split[index])
				return (ft_free(split));
			break ;
		}
		i = i + j;
		j = 0;
	}
	split[index] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;

	if (!s)
		return (NULL);
	count = word_count(s, c);
	if (count == 0 || ft_strlen(s) == 0)
	{
		split = (char **)malloc(sizeof(char *));
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = (char **)malloc((word_count(s, c) + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	split = splitter(split, s, c, count);
	return (split);
}
