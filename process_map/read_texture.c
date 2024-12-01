/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:35:10 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/01 11:28:56 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_texture(void *mlx_ptr, char *file_path, t_img *texture, int img_pix)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file_path, &img_pix, &img_pix);
	if (!texture->img_ptr)
	{
		print_error("Failed to load texture from");
		return;
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
		print_error("Failed to get data address for texture");
}

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

	pos = 0;
	while (path[pos])
	{
		if (path[pos] == ' ' || path[pos] == '\t')
			return (1);
		pos++;
	}
	remove_trailing_whitespace(path);
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
	static char	**texture_fields[4];

	texture_fields[0] = &texture->north_texture,
	texture_fields[1] = &texture->south_texture,
	texture_fields[2] = &texture->west_texture,
	texture_fields[3] = &texture->east_texture;
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
			return (print_error("Invalid texture"), 1);
		i++;
	}
	set_texture(data->mlx->mlx_ptr, data->texture->north_texture, &data->texture->north, data->texture->img_pix);
	set_texture(data->mlx->mlx_ptr, data->texture->south_texture, &data->texture->south, data->texture->img_pix);
	set_texture(data->mlx->mlx_ptr, data->texture->east_texture, &data->texture->east, data->texture->img_pix);
	set_texture(data->mlx->mlx_ptr, data->texture->west_texture, &data->texture->west, data->texture->img_pix);
	set_texture(data->mlx->mlx_ptr, "./img/door.xpm", &data->texture->door, data->texture->img_pix);
	return (0);
}
