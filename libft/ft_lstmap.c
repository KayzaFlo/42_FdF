/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:05:49 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/19 15:34:02 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mlst;
	t_list	*new;

	if (!lst || !f)
		return (0);
	mlst = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&mlst, del);
			return (0);
		}
		if (!mlst)
			mlst = new;
		else
			ft_lstadd_back(&mlst, new);
		lst = lst->next;
	}
	return (mlst);
}
