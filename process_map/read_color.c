/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:57:24 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/06 17:57:33 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Parse RGB values, store them in an array with transparency set to 0.
 * 
 * @param line
 * @param trgb
 * @return int 0 if successful, -1 on error
 */
 /*
int	parse_trgb_values(const char *line, int trgb[4])
{
	int	pos;
	int	comma_count;
	int	i;

	pos = 0;
	comma_count = 0;
	i = 1;
	if (check_for_spaces(line) != 0)
		return (-1);
	trgb[0] = 0;
	skip_identifier(line, &pos);
	// Parse each RGB value and check comma separation
	while (i <= 3)
	{
		trgb[i] = parse_single_value(line, &pos);
		if (trgb[i] == -1)
			return (-1);
		i++;
		// Check for comma if not the last value
		if (i <= 3)
		{
			if (parse_comma_separator(line, &pos) != 0)
				return (-1);
			comma_count++;
		}
	}
	return (validate_end_of_line(line, pos, comma_count));
}
*/
/**
 * @brief get color identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
static int	color_identifier(const char *line)
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
static int read_texture_line(char *line, t_texture *texture)
{
	int	identifier;
	int	trgb[4] = {0, 0, 0, 0};

	line = skip_whitespaces(line);
	identifier = color_identifier(line);
	if (identifier == -1)
		return (-1;
	if (parse_trgb_values(line, trgb, identifier) != 0)
		return (-1);
	if (identifier == 0)
		texture->floor_color = create_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
	else if (identifier == 1)
		texture->ceiling_color = create_trgb(trgb[0], trgb[1], trgb[2], trgb[3]);
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
			return (ft_printf("Error\nInvalid color line: %s\n", text[i]), 1);
		i++;
	}
	return (0);
}

