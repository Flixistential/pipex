/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:26:56 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

int	ft_hex_len(unsigned int num)
{
	int	count;

	count = 0;
	while (num >= 16)
	{
		num = num / 16;
		count++;
	}
	count ++;
	return (count);
}

int	ft_print_hex(unsigned int num, char c)
{
	int	len;

	if (num >= 16)
	{
		ft_print_hex(num / 16, c);
	}
	if (c == 'x')
		write(1, &"0123456789abcdef"[num % 16], 1);
	if (c == 'X')
		write(1, &"0123456789ABCDEF"[num % 16], 1);
	len = ft_hex_len(num);
	return (len);
}
