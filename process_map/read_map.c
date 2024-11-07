/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/07 17:29:51 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief get map identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
static int	map_identifier(char *line)
{
	if (ft_strncmp(line, "1", 1) == 0)
		return (0);
	return (-1);
}

static bool	is_valid_border_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_valid_middle_line(char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	i = 1;
	if (line[0] != '1' || line[len - 1] != '1')
		return (false);
	while (i < (len - 1))
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' &&
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief read each map line and assign to map array if valid
 * only the first and last map line is all 1s
 *the rest of the lines, the first and last char must be 1
 *in between, it can contain 0, 1, N, S, E, W
 * @param line
 * @param texture
 * @return int 
 */
static int	read_map_line(char *line, char **map, char **line_array, int i)
{
	int	identifier;

	line = skip_whitespaces(line);
	if (is_empty_line(line))
	{
		ft_printf("IM HERE1\n", 1);
		return (-1);
	}
	identifier = map_identifier(line);
	if (identifier == -1)
		return (0);
	if (i == 0)
	{	
		if (!is_valid_border_line(line))
		{
			ft_printf("IM HERE2\n", 1);
			return (-1);
		}
	}
	else if (line_array[i + 1] == NULL)
	{	
		if (!is_valid_border_line(line))
		{
			ft_printf("IM HERE3\n", 1);
			return (-1);
		}
	}
	else
	{
		if (!is_valid_middle_line(line))
		{
			ft_printf("IM HERE4\n", 1);
			return (-1);
		}
	}
	*map++ = ft_strdup(line);
	return (0);
}

/**
 * @brief Iterate through the provided text array to find map

 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_map(t_data *data, char **text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (read_map_line(text[i], data->map, text, i) != 0)
			return (ft_printf("Error\nInvalid map: %s\n", text[i]), 1);
		i++;
	}
	return (0);
}
