/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:39:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/25 15:43:48 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	drawline(t_vector2 startpos, t_vector2 endpos, t_data *data, t_vector2 gradient)
{
	float		step;
	float		i;
	float		x;
	float		y;
	float		dx;
	float		dy;
	int			color;

	dx = endpos.x - startpos.x;
	dy = endpos.y - startpos.y;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = startpos.x;
	y = startpos.y;
	i = 1;
	while (i <= step)
	{
		color = (gradient.x * (1 - i / step)) + (gradient.y * (i / step));
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		x += dx;
		y += dy;
		i += 1;
	}
	return (0);
}

int	drawarr(t_data *data, t_vector2 gradient)
{
	t_vector2	grad;
	t_vector2	cursor;
	t_vector2	startdraw;
	t_vector2	enddraw;
	int			isosize;
	float		amp;

	amp = .1f;
	cursor.x = 0;
	isosize = 32;
	while (cursor.x < data->field_size.x)
	{
		cursor.y = 0;
		while (cursor.y < data->field_size.y)
		{
			startdraw.x = data->view_pos.x + cursor.x * isosize + cursor.y * isosize;
			startdraw.y = data->view_pos.y + cursor.x * isosize / 2 - cursor.y * isosize / 2;
			enddraw.x = startdraw.x + isosize;
			enddraw.y = startdraw.y - (data->field[cursor.x + 1][cursor.y] * amp - 1) * isosize / 2;
			startdraw.y -= (data->field[cursor.x][cursor.y] * amp) * isosize / 2;
			grad.x = gradient.x + gradient.y * data->field[cursor.x][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
			grad.y = gradient.x + gradient.y * data->field[cursor.x + 1][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
			drawline(startdraw, enddraw, data, grad);
			startdraw.y += (data->field[cursor.x][cursor.y] * amp) * isosize / 2;
			enddraw.x = startdraw.x + isosize;
			enddraw.y = startdraw.y - (data->field[cursor.x][cursor.y + 1] * amp + 1) * (isosize / 2);
			startdraw.y -= (data->field[cursor.x][cursor.y] * amp) * isosize / 2;
			grad.x = gradient.x + gradient.y * data->field[cursor.x][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
			grad.y = gradient.x + gradient.y * data->field[cursor.x][cursor.y + 1] / (data->rangeheight.y - data->rangeheight.x);
			drawline(startdraw, enddraw, data, grad);
			startdraw.y += (data->field[cursor.x][cursor.y] * amp) * isosize / 2;
			cursor.y++;
		}
		cursor.x++;
	}
	return (0);
}