/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:04:07 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	i;

	if (str == NULL)
	{
		ft_print_str("(null)");
		return (6);
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_format(va_list list, char str)
{
	int	len;

	if (str == 'c')
		len = ft_putchar(va_arg(list, int));
	else if (str == 's')
		len = (ft_print_str(va_arg(list, char *)));
	else if (str == 'p')
		len = ft_print_adress(va_arg(list, void *));
	else if (str == 'd' || str == 'i')
		len = ft_print_int(va_arg(list, int));
	else if (str == 'u')
		len = ft_print_u(va_arg(list, unsigned int));
	else if (str == 'x' || str == 'X')
		len = ft_print_hex(va_arg(list, unsigned int), str);
	else if (str == '%')
		len = ft_putchar('%');
	else
		len = ft_putchar(str);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	list;

	va_start(list, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format(list, str[i + 1]);
			i ++;
		}
		else
		{
			len += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(list);
	return (len);
}
