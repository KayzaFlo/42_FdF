/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:39:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/23 14:42:02 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

float	ft_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	drawline(t_vector2 startpos, t_vector2 endpos, t_mlxrefs *mlxrefs)
{
	int			step;
	int			i;
	float		x;
	float		y;
	float		dx;
	float		dy;

	dx = endpos.x - startpos.x;
	dy = endpos.y - startpos.y;
	if (ft_abs(dx) >= ft_abs(dy))
		step = ft_abs(dx);
	else
		step = ft_abs(dy);
	dx /= step;
	dy /= step;
	x = startpos.x;
	y = startpos.y;
	i = 1;
	while (i <= step)
	{
		mlx_pixel_put(mlxrefs->mlx_ptr, mlxrefs->win_ptr, x, y, 0x00FF00);
		x += dx;
		y += dy;
		i += 1;
	}
	return (0);
}
