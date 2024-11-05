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
		// Check if line starts with a valid identifier and is followed by whitespace or end
		if (ft_strncmp(line, id[i], len) == 0 && 
			((line[len] >= 9 && line[len] <= 13) || line[len] == 20 || line[len] == '\0'))
		{
			if (found[i]) 
			{
				printf("Error: Duplicate identifier found: %s\n", id[i]);
				return (-1);
			}
			found[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief skip leading white spaces 
 * 
 * @param line
 * @return char
 */
static const char	*skip_whitespaces(const char *line) 
{
	while ((*line >= 9 && *line <= 13) || *line == 20) 
		line++;
	return (line);
}

/**
 * @brief check for main 6 identifier  
 * "if (result == 0) and if (all_id_found)": this condition means '1' can only appear 
 * after 6 identifiers is found.
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
			{
				ft_printf("Error: Invalid identifier in line: %s\n", line);
				return (false);
			}
		}
		else
		{
			ft_printf("Error: Misplaced '1' or unknown identifier in line: %s\n", line);
			return (false);
		}
	}
	return (true);
}

/**
 * @brief skip leading whitspaces, skip empty lines, check for id and '1'
 * @param line
 * @param found
 * @param all_id_found 
 * @return bool 
 */
static bool	is_line_valid(const char *line, int *found, bool all_id_found)
{
	line = skip_whitespaces(line);
	if (*line == '\0')
        	return (true);
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
	int	found[6] = {0};
	int	i;
	int	j;
	const char	*id[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	bool	all_id_found;

	i = 0;
	j = 0;
	all_id_found = false;
	while (text[i])
	{
		if (!is_line_valid(text[i], found, all_id_found))
			return (1);
		all_id_found = all_identifiers_found(found);
		i++;
	}
	if (!all_id_found)
	{
		while (j < 6)
		{
			if (!found[j])
			{
				ft_printf("Error: Missing identifier: %s\n", id[j]);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

