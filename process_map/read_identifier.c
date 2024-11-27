/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:32:40 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/26 20:57:38 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief checks if all id found
 * 
 * @param found
 * @return bool
 */
static bool	all_identifiers_found(int *found)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!found[i])
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief checks if line contains valid identifier, flag out if duplicate
 * 
 * @param line
 * @param found
 * @return int
 */
static int	check_id(const char *line, int *found)
{
	int	i;
	int	len;
	const char	*id[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	while (i < 6)
	{
		len = ft_strlen(id[i]);
		if (ft_strncmp(line, id[i], len) == 0 && 
			((line[len] == ' ' || line[len] == '\t' || line[len] == '\0')))
		{
			if (found[i])
				return (ft_printf("Error\nDuplicate identifier found\n"), -1);
			found[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief check for main 6 identifier  
 * "if (result == 0) and if (all_id_found)": this condition means '1' can only appear 
 * after 6 identifiers is found.
 *
 * @param line
 * @param found
 * @param all_id_found 
 * @return bool 
 */
static bool	check_id_and_one(const char *line, int *found, bool all_id_found)
{
	int	result;

	result = check_id(line, found);
	if (result == -1)
		return (false);
	if (result == 0)
	{
		if (all_id_found)
		{
			if (line[0] != '1')
				return (ft_printf("Error\nInvalid identifier\n"), false);
		}
		else
			return (ft_printf("Error\nMisplaced '1' or unknown identifier\n"), false);
	}
	return (true);
}

/**
 * @brief skip leading whitspaces, skip empty lines, check for id and '1'
 *
 * @param line
 * @param found
 * @param all_id_found 
 * @return bool 
 */
static bool	is_line_valid(char *line, int *found, bool all_id_found)
{
	if (is_empty_line(line))
        	return (true);
	line = skip_whitespaces(line);
	return (check_id_and_one(line, found, all_id_found));
}

/**
 * @brief main function to validate identifiers
 * 
 * @param text
 * @return int 
 */

int	check_identifiers(char **text)
{
	int		found[6];
	int		i;
	int		j;
	bool	all_id_found;

	ft_memset(found, 0, sizeof(found));
	i = -1;
	j = -1;
	all_id_found = false;
	while (text[++i])
	{
		if (!is_line_valid(text[i], found, all_id_found))
			return (1);
		all_id_found = all_identifiers_found(found);
	}
	if (!all_id_found)
	{
		while (++j < 6)
		{
			if (!found[j])
				return (ft_printf("Error\nMissing identifier\n"), 1);
		}
	}
	return (0);
}

