/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:49:55 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/21 12:38:21 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_byte;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	dst_byte = dst;
	i = -1;
	while (++i < n)
		dst_byte[i] = *((unsigned char *)src + i);
	return (dst);
}
