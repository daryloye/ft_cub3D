/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:10:21 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 18:08:18 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	x;

	if (n == 0)
		return (s);
	p = (unsigned char *) s;
	x = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		p[i] = x;
		i++;
	}
	return (s);
}
