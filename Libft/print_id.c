/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:42:30 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:42:33 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_id(int n)
{
	int		i;
	long	nb;

	nb = n;
	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	print_id(int n)
{
	ft_putnbr_fd(n, 1);
	return (len_id(n));
}
