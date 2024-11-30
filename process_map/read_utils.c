/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:53:00 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/30 22:39:24 by daong            ###   ########.fr       */
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

/**
 * @brief remove trailing white spaces 
 * 
 * @param line
 * @return char
 */
void	remove_trailing_whitespace(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (len >= 0 && (line[len] == ' ' || line[len] == '\n' || line[len] == '\t'))
		line[len--] = '\0';
}

/**
 * @brief check for empty line
 *
 * @param line
 * @return bool 
 */
bool	is_empty_line(char *line)
{
	if (line == NULL || *line == '\0')
			return (true);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

/**
 * @brief writes error message to stderror
 * 
 * @param str 
 */
void	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return ;
}
