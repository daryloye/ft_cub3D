/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:32:40 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/04 20:32:43 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief check identifiers make sure all 6 identifiers appear once
 * 
 * @param fd 
 * @return char** 
 */

int	check_identifiers(char **text)
{
	int	found[6] = {0};
	int	i;
	int	j;
	const char	*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	j = 0;
	while (text[i])
	{
		while (j < 6)
		{
			if (ft_strncmp(text[i], identifiers[j], ft_strlen(identifiers[j])) == 0)
			{
				if (found[j])
				{
					ft_printf("Error: Duplicate identifier found: %s\n", identifiers[j]);
					return (1);
				}
				found[j] = 1;
			}
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 6)
	{
		if (!found[j])
		{
			ft_printf("Error: Missing identifier: %s\n", identifiers[j]);
			return (1);
		}
		j++;
	}
	return (0);
}

