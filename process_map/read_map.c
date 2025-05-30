/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 13:05:23 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief read each map line and assign to map array if valid
 *
 * @param line
 * @param data
 * @param text
 * @param i
 * @return int 0 if success, -1 if fail 
 */
static int	handle_map_initialization(t_data *data, char **text, int i)
{
	int	j;

	get_map_size(data, text, i);
	data->map = ft_calloc(data->map_size_y + 1, sizeof(char *));
	if (!data->map)
		return (-1);
	j = i;
	while (j - i < data->map_size_y)
	{
		data->map[j - i] = ft_strdup(text[j]);
		j++;
	}
	data->map[data->map_size_y] = NULL;
	return (0);
}

static int	validate_and_process_map(t_data *data)
{
	if (check_map(data) != 0)
		return (-1);
	create_temp_map_with_border(data);
	if (!is_map_enclosed(data))
		return (-1);
	replace_whitespace_with_zero_mod(data->map, data->map_size_y);
	return (0);
}

static int	read_map_line(char *line, t_data *data, char **text, int i)
{
	int	identifier;

	identifier = map_identifier(line);
	if (identifier == -1)
		return (0);
	if (identifier == 0)
	{
		if (data->map)
			free_map(data);
		if (!data->map)
		{
			if (handle_map_initialization(data, text, i) != 0)
				return (-1);
			if (validate_and_process_map(data) != 0)
				return (-1);
		}
	}
	return (0);
}

/**
 * @brief Iterate through the provided text array to find map
 * remove /n character for each row in map
 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_map(t_data *data, char **text)
{
	int	i;

	i = -1;
	while (text[++i])
	{
		if (read_map_line(text[i], data, text, i) != 0)
			return (print_error("Invalid map"), 1);
		if (data->map)
			break ;
	}
	if (!data->map)
		return (print_error("Map could not be initialized"), 1);
	sanitise_map(data);
	update_map_size(data);
	return (0);
}
