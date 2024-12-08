/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 12:49:58 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
Find the first and last positions of consecutive '1's in the current line
Error if no '1' found on the current line
Handle special case for the first row (check 2nd row alignment)
->Check if the first '1' in the second row is within the 
range of first and last '1' of the first row
*/
/*
int	check_leading_spaces(t_data *data)
{
	int	i;
	int	prev_first_one;
	int	prev_last_one;

	i = 0;
	prev_first_one = -1;
	prev_last_one = -1;
	while (i < data->map_size_y)
	{
		if (process_row(data, i, &prev_first_one, &prev_last_one) == -1)
			return (-1);
		i++;
	}
	return (0);
}
*/
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
//	if (check_leading_spaces(data) != 0)
//		return (-1);
	create_temp_map_with_border(data);
//	replace_whitespace_with_zero_mod(data->temp_map, data->map_size_y);
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

void	update_map_size(t_data *data)
{
	int	new_size_x;
	int	y;

	new_size_x = 0;
	y = -1;
	while (data->map[++y])
		new_size_x = ft_max(ft_strlen(data->map[y]), new_size_x);
	data->map_size_x = new_size_x;
	return ;
}

void	sanitise_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '\n')
				data->map[y][x] = '\0';
		}
	}
	return ;
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
	sanitise_map(data);
	update_map_size(data);
	return (0);
}
