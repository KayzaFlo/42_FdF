/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:17 by fgeslin           #+#    #+#             */
/*   Updated: 2022/10/24 12:39:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_wc(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep)
			if (str[i + 1] == '\0' || str[i + 1] == sep)
				count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		shift;
	int		len;
	int		count;

	if (!s)
		return (NULL);
	tab = malloc((get_wc(s, c) + 1) * sizeof(*tab));
	if (tab == NULL)
		return (NULL);
	shift = 0;
	count = 0;
	while (count < get_wc(s, c))
	{
		len = 0;
		while (s[shift] == c && s[shift])
			shift++;
		while (s[shift + len] != c && s[shift + len])
			len++;
		tab[count] = ft_substr(s, shift, len);
		shift += len;
		count++;
	}
	tab[count] = NULL;
	return (tab);
}
