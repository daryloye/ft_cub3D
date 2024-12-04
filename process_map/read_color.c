/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:57:24 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/04 12:27:37 by daong            ###   ########.fr       */
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
static int parse_value(char *line, int *start)
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
static int	parse_comma(char *line, int *start, int comma_count)
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
static int	skip_initial_whitespace(char *line, int start)
{
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	return (start);
}

/**
 * @brief Parse RGB values, check for rgb value and comma separation in the while loop
 *
 * @param line
 * @param start
 * @param color
 * @return int 0 if successful, -1 on error
 */
static int	parse_rgb_values(char *line, int *start, int color[4])
{
	int	comma_count;
	int	j;

	comma_count = 0;
	j = 1;
	while (j <= 3)
	{
		color[j] = parse_value(line, start);
		if (color[j] == -1)
			return (-1);
		j++;
		if (j <= 3)
		{
			if (parse_comma(line, start, comma_count) != 0)
				return (-1);
			comma_count++;
		}
	}
	return (0);
}

/**
 * @brief Parse tRGB values, store them in an array with transparency set to 0.
 *
 * @param line
 * @param color
 * @return int 0 if successful, -1 on error
 */
static int	parse_trgb_values(char *line, int color[4])
{
	int	start;

	remove_trailing_whitespace(line);
	start = skip_initial_whitespace(line, 2);	
	if (check_for_spaces(&line[start]) != 0)
		return (-1);
	color[0] = 0;
	if (parse_rgb_values(line, &start, color) != 0)
		return (-1);
	if (line[start] != '\0')
		return (-1);
	return (0);
}

/**
 * @brief get color identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
static int	color_identifier(char *line)
{
	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "F\t", 2) == 0))
		return (0);
	if ((ft_strncmp(line, "C ", 2) == 0) || (ft_strncmp(line, "C\t", 2) == 0))
		return (1);
	return (-1);
}

/**
 * @brief read each color line and assign the correct trgb value
 * 
 * @param line
 * @param texture
 * @return int return 0 if successful, -1 on error
 */
static int read_color_line(char *line, t_texture *texture)
{
	int	identifier;
	int	color[4] = {0, 0, 0, 0};

	line = skip_whitespaces(line);
	identifier = color_identifier(line);
	if (identifier == -1)
		return (0);
	if (parse_trgb_values(line, color) != 0)
		return (-1);
	if (identifier == 0)
		texture->floor_color = trgb(color[0], color[1], color[2], color[3]);
	else if (identifier == 1)
		texture->ceiling_color = trgb(color[0], color[1], color[2], color[3]);
    return (0);
}

/**
 * @brief Iterate through the provided text array to find color definitions

 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_color(t_data *data, char **text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (read_color_line(text[i], data->texture) != 0)
			return (print_error("Invalid color line"), 1);
		i++;
	}
	return (0);
}

