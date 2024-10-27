/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:15:19 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:41:47 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	phonebook(char spec, va_list args)
{
	int	i;

	if (spec == 'c')
		i = print_c ((char) va_arg(args, int));
	else if (spec == 's')
		i = print_s (va_arg(args, char *));
	else if (spec == 'p')
		i = print_p (va_arg(args, void *));
	else if (spec == 'd' || spec == 'i')
		i = print_id (va_arg(args, int));
	else if (spec == 'u')
		i = print_u (va_arg(args, unsigned int));
	else if (spec == 'x')
		i = print_x(va_arg(args, unsigned int), "0123456789abcdef");
	else if (spec == 'X')
		i = print_x(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (spec == '%')
		i = print_percent();
	else
		i = -1;
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		res;
	int		pb;

	va_start (args, str);
	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			write (1, str + i, 1);
			res++;
		}
		else
		{
			pb = phonebook (str[++i], args);
			if (pb >= 0)
				res += pb;
		}
		i++;
	}
	va_end (args);
	return (res);
}
