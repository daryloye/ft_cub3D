/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:43:22 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:45:01 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_unsigned(unsigned int n, int fd)
{
	char	last_digit;

	if (n >= 10)
	{
		ft_putnbr_fd_unsigned(n / 10, fd);
		ft_putnbr_fd_unsigned(n % 10, fd);
	}
	else
	{
		last_digit = n + '0';
		write (fd, &last_digit, 1);
	}
}

int	len_u(unsigned int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	print_u(unsigned int n)
{
	ft_putnbr_fd_unsigned(n, 1);
	return (len_u(n));
}
