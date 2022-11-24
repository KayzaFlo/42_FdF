/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:22:17 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/21 13:47:18 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if ((size_t)ft_strlen(s) < len)
		len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (i + start < (size_t)ft_strlen(s))
			str[i] = s[i + start];
		else
			str[i] = 0;
	}
	str[i] = 0;
	return (str);
}
