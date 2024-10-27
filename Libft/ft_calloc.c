/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:57:37 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 18:02:51 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;

	dest = (char *)malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, nmemb * size);
	return (dest);
}
