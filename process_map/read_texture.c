/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:35:10 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/06 02:01:32 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief get the path of the texture file
 * 
 * @param line
 * @param texture
 * @return char * 
 */
static char *find_path(char *line)
{
	int		i;
	int		j;
	int		start;
	char*	path;

	i = 3;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	path = calloc(i - start + 1, sizeof(char));
	while (j < (i - start))
	{
		path[j] = line[start + j];
		j++;
    }
    return (path);
}

/**
 * @brief get texture identifier
 * 
 * @param line
 * @param texture
 * @return int 
 */
static int  texture_identifier(const char *line)
{
	if ((ft_strncmp(line, "NO ", 3) == 0) || (ft_strncmp(line, "NO\t", 3) == 0))
		return (0);
	if ((ft_strncmp(line, "SO ", 3) == 0) || (ft_strncmp(line, "SO\t", 3) == 0))
		return (1);
	if ((ft_strncmp(line, "WE ", 3) == 0) || (ft_strncmp(line, "WE\t", 3) == 0))
		return (2);
	if ((ft_strncmp(line, "EA ", 3) == 0) || (ft_strncmp(line, "EA\t", 3) == 0))
		return (3);
	return (-1);
}

/**
 * @brief check file is .xpm
 * 
 * @param path 
 * @param suffix 
 * @return int 
 */
static int	check_file_name(char *path, char *suffix)
{
	int	pos;

	pos = ft_strlen(path) - 4;
	if (pos < 0 || ft_strncmp(path + pos, suffix, ft_strlen(suffix)) != 0)
		return (1);
	return (0);
}

/**
 * @brief read each texture line and assign if each texture .xpm file is valid
 * 
 * @param line
 * @param texture
 * @return int 
 */
static int read_texture_line(char *line, t_texture *texture)
{
	int	identifier;
	char	*path;
	char	**texture_fields[] = {
		&texture->north_texture,
		&texture->south_texture,
		&texture->west_texture,
		&texture->east_texture
	};

	line = skip_whitespaces(line);
	identifier = texture_identifier(line);
	if (identifier == -1)
		return (0);
	path = find_path(line);
	if (!path)
		return (-1);
	if (check_file_name(path, ".xpm") != 0)
	{
		free(path);
		return (-1);
	}
	free(*texture_fields[identifier]);
	*texture_fields[identifier] = path;
	return (0);
}

/**
 * @brief Iterate through the provided text array to find texture definitions

 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_textures(t_data *data, char **text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (read_texture_line(text[i], data->texture) != 0)
			return (ft_printf("Error\nInvalid texture line: %s\n", text[i]), 1);
		i++;
	}
	return (0);
}
