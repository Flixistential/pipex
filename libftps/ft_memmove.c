/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:43:06 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:53:03 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	if (!dst || !src)
		return (NULL);
	a = (char *)src;
	b = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		while (len-- > 0)
			b[len] = a[len];
	}
	else
	{
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dst);
}
