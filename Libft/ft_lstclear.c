/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:20:37 by daong             #+#    #+#             */
/*   Updated: 2024/05/31 13:12:18 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*temp;

	x = *lst;
	while (x != NULL)
	{
		temp = x->next;
		del(x->content);
		free(x);
		x = temp;
	}
	*lst = NULL;
}
