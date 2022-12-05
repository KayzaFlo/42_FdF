/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tween.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:02:33 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 15:02:43 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	tween_color(t_int2 gradient, float x)
{
	int	t;
	int	r;
	int	g;
	int	b;

	x = -(cos(3.1415f * x) - 1) / 2;
	t = ((gradient.x >> 24) & 0xFF) * (1 - x) + ((gradient.y >> 24) & 0xFF) * x;
	r = ((gradient.x >> 16) & 0xFF) * (1 - x) + ((gradient.y >> 16) & 0xFF) * x;
	g = ((gradient.x >> 8) & 0xFF) * (1 - x) + ((gradient.y >> 8) & 0xFF) * x;
	b = (gradient.x & 0xFF) * (1 - x) + (gradient.y & 0xFF) * x;
	return (t << 24 | r << 16 | g << 8 | b);
}
