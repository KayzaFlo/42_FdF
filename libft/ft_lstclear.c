/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:24:59 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/21 17:09:03 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextdel;

	if (!lst || !del)
		return ;
	nextdel = 0;
	while (*lst)
	{
		nextdel = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = nextdel;
	}
}
