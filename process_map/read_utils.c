/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:53:00 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/05 16:53:03 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief skip leading white spaces 
 * 
 * @param line
 * @return char
 */
char	*skip_whitespaces(char *line) 
{
	while (*line == ' ' || *line == '\t') 
		line++;
	return (line);
}

void	remove_trailing_whitespace(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (len >= 0 && (line[len] == ' ' || line[len] == '\n' || line[len] == '\t'))
		line[len--] = '\0';
}
