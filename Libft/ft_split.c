/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:59:00 by daong             #+#    #+#             */
/*   Updated: 2024/05/31 13:51:02 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			word_count++;
		i++;
	}
	return (word_count);
}

static int	get_word_len(char const *s, char c, int i)
{
	int	word_len;

	word_len = 0;
	while (s[i] && s[i] != c)
	{
		word_len++;
		i++;
	}
	return (word_len);
}

static char	*copy_word(char const *s, int i, int word_len, char *dest)
{
	int	x;

	x = 0;
	while (x < word_len)
	{
		dest[x] = s[i];
		x++;
		i++;
	}
	dest[x] = '\0';
	return (dest);
}

static int	make_words(char const *s, char c, char **dest, int word_count)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	while (word < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		word_len = get_word_len(s, c, i);
		dest[word] = (char *)malloc(word_len + 1);
		if (!dest[word])
		{
			while (word > 0)
				free(dest[--word]);
			free(dest);
			return (0);
		}
		copy_word(s, i, word_len, dest[word]);
		i += word_len;
		word++;
	}
	dest[word] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**dest;

	if (!s)
		return (NULL);
	word_count = get_word_count(s, c);
	dest = (char **)malloc(sizeof (char *) * (word_count + 1));
	if (!dest)
		return (NULL);
	if (!make_words(s, c, dest, word_count))
		return (NULL);
	return (dest);
}
