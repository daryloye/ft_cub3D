/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:58:46 by daong             #+#    #+#             */
/*   Updated: 2024/05/30 17:50:13 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_cmp(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (str_cmp(s1[start], set) == 1)
		start++;
	return (start);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	count;

	count = ft_strlen(s1) - 1;
	end = 0;
	while (str_cmp(s1[count], set) == 1)
	{
		end++;
		count--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	i;
	size_t	len;
	char	*dest;

	if (!s1)
		return (NULL);
	start = get_start(s1, set);
	if (start >= ft_strlen(s1))
		len = 0;
	else
		len = ft_strlen(s1) - start - get_end(s1, set);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s1[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
