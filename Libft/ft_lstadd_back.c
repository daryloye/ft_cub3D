/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:18:47 by daong             #+#    #+#             */
/*   Updated: 2024/05/31 13:11:47 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*x;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		x = *lst;
		while (x->next != NULL)
			x = x->next;
		x->next = new;
	}
}
