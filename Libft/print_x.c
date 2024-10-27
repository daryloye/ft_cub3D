/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bigx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:43:10 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:44:11 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_x(unsigned int nb)
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

int	print_x(unsigned int n, char *base)
{
	ft_putnbr_base(n, base);
	return (len_x(n));
}
