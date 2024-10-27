/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:26:00 by daong             #+#    #+#             */
/*   Updated: 2024/06/05 11:42:12 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_rpt(char *base)
{
	int	x;
	int	y;

	if (ft_strlen (base) == 0 || ft_strlen (base) == 1)
		return (0);
	x = 0;
	while (base[x + 1])
	{
		y = x + 1;
		while (base[y])
		{
			if (base[x] == base[y])
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	check_size(char *base)
{
	int	x;

	x = 0;
	while (base[x])
	{
		if (base[x] == '+' || base[x] == '-')
			return (0);
		else if (base[x] == ' ' || (base[x] >= '\t' && base[x] <= '\r'))
			return (0);
		x++;
	}
	return (1);
}

void	ft_putnbr_base(unsigned long nbr, char *base)
{
	size_t	len;

	len = ft_strlen (base);
	if (check_rpt (base) == 1 && check_size (base) == 1)
	{
		if (nbr >= len)
		{
			ft_putnbr_base (nbr / len, base);
			ft_putnbr_base (nbr % len, base);
		}
		else
			write (1, &base[nbr], 1);
	}
}
