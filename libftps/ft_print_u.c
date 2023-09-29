/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:56:06 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:57:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

int	ft_print_stru(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_len(unsigned int n)
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

char	*ft_itoau(unsigned int n)
{
	int					i;
	unsigned int		cpy;
	long				nb;
	char				*ptr;

	nb = n;
	cpy = 0;
	i = ft_len(nb);
	ptr = (char *)malloc((sizeof(char) * (i + 2)));
	if (!ptr)
		return (NULL);
	ptr[i + 1] = '\0';
	while (i >= (int)cpy)
	{
		ptr[i] = (nb % 10) + 48;
		i--;
		nb = nb / 10;
	}
	return (ptr);
}

int	ft_print_u(unsigned int num)
{
	char	*str;
	int		len;

	len = 0;
	if (num == 0)
	{
		len += write(1, "0", 1);
	}
	else
	{
		str = ft_itoau(num);
		len += ft_print_stru(str);
		free(str);
	}
	return (len);
}
