/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:11:07 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/21 13:22:29 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_size;

	if (!needle[0])
		return ((char *)hay);
	i = 0;
	needle_size = ft_strlen(needle);
	while (hay[i] && i < len)
	{
		if (len - i < needle_size)
			return (NULL);
		if (ft_strncmp(hay + i, needle, needle_size) == 0)
			return ((char *)(hay + i));
		i++;
	}
	return (NULL);
}
