/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:53:04 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 12:02:10 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief get map identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
int	map_identifier(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "1", 1) == 0)
		return (0);
	return (-1);
}

/**
 * @brief get map size and assign to data
 *
 * @param data
 * @return int  0 if success
 */
int	get_map_size(t_data *data, char **text, int i)
{
	int	map_size_x;
	int	map_size_y;
	int	row_len;
	int	j;

	map_size_x = 0;
	map_size_y = 0;
	j = i;
	while (text[i + map_size_y])
		map_size_y++;
	while (map_size_y > 0 && (text[i + map_size_y - 1] == NULL
			|| text[i + map_size_y - 1][0] == '\0'
		|| text[i + map_size_y - 1][0] == '\n'))
		map_size_y--;
	while (j < (i + map_size_y))
	{
		row_len = ft_strlen(text[j]);
		if (row_len > map_size_x)
			map_size_x = row_len;
		j++;
	}
	data->map_size_x = map_size_x;
	data->map_size_y = map_size_y;
	return (0);
}

/**
 * @brief Assign F to border (if), pad the remaining
 *if the row is shorter than longest row with 'F' (else: it replaces \n wih 'F')
 *
 * @param data
 */
static void	fill_temp_map_row(t_data *data, int i)
{
	int	j;
	int	row_len;

	j = 0;
	while (j < data->map_size_x + 2)
	{
		if (i == 0 || i == data->map_size_y + 1 || j == 0
			|| j == data->map_size_x + 1)
			data->temp_map[i][j] = 'F';
		else
		{
			row_len = ft_strlen(data->map[i - 1]);
			if (j - 1 < row_len && data->map[i - 1][j - 1] != '\n')
				data->temp_map[i][j] = data->map[i - 1][j - 1];
			else
				data->temp_map[i][j] = 'F';
		}
		j++;
	}
//	data->temp_map[i][j] = '\0';
}

void	create_temp_map_with_border(t_data *data)
{
	int	i;

	i = 0;
	data->temp_map = (char **)ft_calloc(data->map_size_y + 2, sizeof(char *));
	while (i < data->map_size_y + 2)
	{
		data->temp_map[i] = (char *)ft_calloc(data->map_size_x + 2,
				sizeof(char));
		fill_temp_map_row(data, i);
		i++;
	}
}
