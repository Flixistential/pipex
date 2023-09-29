/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:01:52 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:54:52 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str || !to_find)
		return (NULL);
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *) str);
	while (str[i] && len > 0)
	{
		while (str[i + j] == to_find[j] && (i + j) < len)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i]);
			if (str[i + j + 1] != to_find[j + 1])
				break ;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
