/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:21:29 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	p;

	if (!s)
		return (NULL);
	p = c;
	i = ft_strlen(s);
	if (p == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == p)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
