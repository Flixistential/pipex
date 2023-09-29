/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:54:00 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:54:31 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

size_t	findend(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(s1) == 0)
		return (0);
	i = (ft_strlen(s1) - 1);
	j = 0;
	while (i >= (ft_strlen(s1) - ft_strlen(set)) && set[j])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i--;
				j = -1;
			}
			j++;
		}
	}
	return (i + 1);
}

size_t	findstart(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(s1) == 0)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(set) && set[j])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i++;
				j = -1;
			}
			j++;
		}
	}
	return (i);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*ptr;

	i = 0;
	if (!s1)
		return (NULL);
	start = findstart(s1, set);
	end = findend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!ptr || !s1)
		return (NULL);
	end = end - start;
	while (i < (end))
	{
		ptr[i++] = s1[start++];
	}
	ptr[i] = '\0';
	return (ptr);
}
