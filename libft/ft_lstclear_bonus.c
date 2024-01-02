/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:39:15 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/09 06:34:06 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*temp;

	node = *lst;
	temp = NULL;
	if (!lst || !del)
		return ;
	while (node)
	{
		temp = node;
		node = node->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
