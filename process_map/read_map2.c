/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:24:01 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 09:28:32 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int find_first_and_last_one(char *row, int *first_one, int *last_one)
{
    int j = 0;

    *first_one = -1;
    *last_one = -1;

    while (row[j])
    {
        if (row[j] == '1')
        {
            if (*first_one == -1)
                *first_one = j;
            *last_one = j;
        }
        j++;
    }

    return (*first_one != -1 && *last_one != -1) ? 0 : -1;
}

static int check_second_row(int first_one, int prev_first_one, int prev_last_one)
{
    if (prev_first_one != -1)
    {
        if (first_one < prev_first_one - 1 || first_one > prev_last_one)
            return (-1);
    }
    return (0);
}

static int check_middle_row(int last_one, int prev_last_one)
{
    int diff;

    if (prev_last_one != -1)
    {
        diff = last_one - prev_last_one;
        if (diff > 1 || diff < -1)
            return (-1);
    }
    return (0);
}

static int check_last_row(int first_one, int last_one, int prev_first_one)
{
    if (prev_first_one < first_one - 1 || prev_first_one > last_one)
        return (-1);
    return (0);
}

int process_row(t_data *data, int i, int *prev_first_one, int *prev_last_one)
{
    int first_one, last_one;

    if (find_first_and_last_one(data->map[i], &first_one, &last_one) == -1)
        return (-1);

    if (i == 1)
    {
        if (check_second_row(first_one, *prev_first_one, *prev_last_one) == -1)
            return (-1);
    }
    else if (i == data->map_size_y - 1)
    {
        if (check_last_row(first_one, last_one, *prev_first_one) == -1)
            return (-1);
    }
    else
    {
        if (check_middle_row(last_one, *prev_last_one) == -1)
            return (-1);
    }

    *prev_first_one = first_one;
    *prev_last_one = last_one;
    return (0);
}

