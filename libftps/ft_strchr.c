/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:16:23 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	p;

	if (!s)
		return (NULL);
	p = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == p)
			return ((char *)&s[i]);
		i++;
	}
	if (p == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
