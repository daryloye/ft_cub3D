/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:42:39 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:42:41 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_p(unsigned long nb)
{
	int	i;

	i = 1;
	while (nb >= 16)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int	print_p(void *ptr)
{
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_base((unsigned long) ptr, "0123456789abcdef");
	return (len_p((unsigned long) ptr) + 2);
}
