/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:57:22 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 17:48:16 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	s;
	size_t	t;

	if (little[0] == '\0')
		return ((char *)(big));
	s = 0;
	while (big[s] && s < len)
	{
		t = 0;
		while (little[t] && s + t < len && little[t] == big[s + t])
		{
			if (little[t + 1] == '\0')
				return ((char *)(big + s));
			t++;
		}
		s++;
	}
	return (0);
}
