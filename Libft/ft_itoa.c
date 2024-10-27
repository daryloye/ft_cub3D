/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:59:07 by daong             #+#    #+#             */
/*   Updated: 2024/05/29 17:05:00 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_neg(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static char	*make_dst(char *dest, int n, int i, long test)
{
	dest[i] = '\0';
	i--;
	dest[i] = test % 10 + '0';
	i--;
	while (test >= 10)
	{
		test = test / 10;
		dest[i] = test % 10 + '0';
		i--;
	}
	if (check_neg(n) == 1)
		dest[0] = '-';
	return (dest);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		i;
	long	x;
	long	test;
	char	*dest;

	x = n;
	digits = 1;
	if (check_neg(n) == 1)
		x = -x;
	test = x;
	while (test >= 10)
	{
		test = test / 10;
		digits++;
	}
	dest = (char *)malloc(check_neg(n) + digits + 1);
	if (!dest)
		return (NULL);
	i = check_neg(n) + digits;
	test = x;
	make_dst(dest, n, i, test);
	return (dest);
}
