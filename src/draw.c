/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:39:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/28 12:57:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	drawline(t_float2 a, t_float2 b, t_data *data, t_int2 gradient)
{
	t_float2	dir;
	float		step;
	float		i;
	int			color;

	dir.x = b.x - a.x;
	dir.y = b.y - a.y;
	if (fabs(dir.x) >= fabs(dir.y))
		step = fabs(dir.x);
	else
		step = fabs(dir.y);
	dir.x /= step;
	dir.y /= step;
	i = 1;
	while (i <= step)
	{
		color = (gradient.x * (1 - i / step)) + (gradient.y * (i / step));
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, a.x, a.y, color);
		a.x += dir.x;
		a.y += dir.y;
		i += 1;
	}
	return (0);
}

int	drawarr(t_data *data, t_int2 gradient)
{
	t_int2		grad;
	t_int2		cursor;
	t_float2	startdraw;
	t_float2	enddraw;
	float		amp;

	amp = .1f;
	cursor.x = 0;
	while (cursor.x < data->field_size.x)
	{
		cursor.y = 0;
		while (cursor.y < data->field_size.y)
		{
			startdraw.x = data->view_pos.x + cursor.x * data->zoom + cursor.y * data->zoom;
			startdraw.y = data->view_pos.y + cursor.x * data->zoom / 2 - cursor.y * data->zoom / 2;
			/* DRAW H LINE */
			if (cursor.x + 1 < data->field_size.x)
			{
				enddraw.x = startdraw.x + data->zoom;
				enddraw.y = startdraw.y - (data->field[cursor.x + 1][cursor.y] * amp - 1) * data->zoom / 2;
				startdraw.y -= (data->field[cursor.x][cursor.y] * amp) * data->zoom / 2;
				grad.x = gradient.x + gradient.y * data->field[cursor.x][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
				grad.y = gradient.x + gradient.y * data->field[cursor.x + 1][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
				drawline(startdraw, enddraw, data, grad);
			}
			/* DRAW V LINE */
			if (cursor.y + 1 < data->field_size.y)
			{
				startdraw.y += (data->field[cursor.x][cursor.y] * amp) * data->zoom / 2;
				enddraw.x = startdraw.x + data->zoom;
				enddraw.y = startdraw.y - (data->field[cursor.x][cursor.y + 1] * amp + 1) * (data->zoom / 2);
				startdraw.y -= (data->field[cursor.x][cursor.y] * amp) * data->zoom / 2;
				grad.x = gradient.x + gradient.y * data->field[cursor.x][cursor.y] / (data->rangeheight.y - data->rangeheight.x);
				grad.y = gradient.x + gradient.y * data->field[cursor.x][cursor.y + 1] / (data->rangeheight.y - data->rangeheight.x);
				drawline(startdraw, enddraw, data, grad);
			}			
			cursor.y++;
		}
		cursor.x++;
	}
	return (0);
}
