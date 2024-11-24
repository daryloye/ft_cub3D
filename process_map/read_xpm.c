/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:45:38 by daong             #+#    #+#             */
/*   Updated: 2024/11/24 22:51:56 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief converts text in fd to array
 * 
 * @param fd 
 * @return char** 
 */
static char	**convert_xpm_to_array(int fd)
{
	int		lines;
	char	*str;
	char	**text;
	char	**temp;

	lines = 0;
	text = ft_calloc(sizeof(char *), lines + 1);
	if (!text)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		text[lines++] = str;
		temp = ft_realloc(text, lines);
		if (!temp)
		{
			while (lines > 0)
				free(text[--lines]);
			return (free(text), NULL);
		}
		text = temp;
		str = get_next_line(fd);
	}
	return (text);
}

int	read_xpm(char *path, t_data *data)
{
	int		fd;
	int		**text;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nImg file not found\n"), 1);
	text = convert_xpm_to_array(fd);
}
