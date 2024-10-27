/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:58:58 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 19:09:40 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc(char **arr, int lines)
{
	char	**dest;
	int		i;

	dest = (char **)ft_calloc(sizeof(char *), lines + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < lines && arr[i])
	{
		dest[i] = arr[i];
		i++;
	}
	free(arr);
	return (dest);
}
