/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:37:37 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

int	len(int n)
{
	int		count;
	long	nb;

	nb = n;
	count = 0;
	if (n < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	int		cpy;
	long	nb;
	char	*ptr;

	nb = n;
	cpy = 0;
	i = len(nb);
	ptr = (char *)malloc((sizeof(char) * (i + 2)));
	if (!ptr)
		return (NULL);
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
		cpy++;
	}
	ptr[i + 1] = '\0';
	while (i >= cpy)
	{
		ptr[i] = (nb % 10) + 48;
		i--;
		nb = nb / 10;
	}
	return (ptr);
}
