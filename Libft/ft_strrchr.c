/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:15:16 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 17:47:30 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	store;

	i = 0;
	store = -1;
	while (s[i])
	{
		if (s[i] == (char) c)
			store = i;
		i++;
	}
	if ((char) c == '\0')
		return ((char *)(s + i));
	else if (store != -1)
		return ((char *)(s + store));
	else
		return (NULL);
}
