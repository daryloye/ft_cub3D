/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:47:55 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 17:51:08 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		while (i < n)
		{
			d[n - i - 1] = s[n - i - 1];
			i++;
		}
	}
	return (dest);
}
