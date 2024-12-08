/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:33:36 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 08:38:50 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Parse the RGB input .cub aka x,x,x. return error if there is a space
 * 
 * @param line
 * @return int 0 if successful, -1 on error
 */
int	check_for_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return (-1);
		i++;
	}
	return (0);
}

/**
 * @brief Parse the RGB input .cub aka x,x,x. return error if there is a space
 * digi_count can happen when you encounter a comma immediately or other non num
 * @param line
 * @param start
 * @return int value if successful, -1 on error
 */
int	parse_value(char *line, int *start)
{
	long	value;
	long	digit_count;

	value = 0;
	digit_count = 0;
	while (line[*start] >= '0' && line[*start] <= '9')
	{
		value = value * 10 + (line[*start] - '0');
		(*start)++;
		digit_count++;
	}
	if (digit_count == 0 || value < 0 || value > 255)
		return (-1);
	return ((int)value);
}

/**
 * @brief Parse the comma in x,x,x and check whether the comma is present 
 *
 * @param line
 * @param start
 * @return int 0 if successful, -1 on error
 */
int	parse_comma(char *line, int *start, int comma_count)
{
	if (line[*start] != ',' && comma_count < 2)
		return (-1);
	(*start)++;
	return (0);
}

/**
 * @brief skip_initial_whitespace
 *
 * @param line
 * @param start
 * @return int start if successful
 */
int	skip_initial_whitespace(char *line, int start)
{
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	return (start);
}
