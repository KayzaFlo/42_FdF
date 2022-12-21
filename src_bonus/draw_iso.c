/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/21 17:55:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

static t_int2	get_gradient(t_data *data, int x, int y)
{
	t_int2	gradient;
	float	height;
	float	maxheight;

	maxheight = data->height.y - data->height.x;
	if (maxheight <= 0)
		maxheight = 1;
	height = data->field[x][y] - data->height.x;
	gradient.x = tween_color(data->gradient, height / maxheight);
	height = data->field[x][y] - data->height.x;
	gradient.y = tween_color(data->gradient, height / maxheight);
	return (gradient);
}

static t_int2	field_to_screen(t_data *data, int x, int y)
{
	t_int2	screen_point;
	int		height;
	float	shrinker;

	shrinker = (float)((int)data->view_dir % 180 - 90) / 45;
	if (shrinker < 0)
		shrinker *= -1;
	shrinker -= 1;
	if (shrinker < 0)
		shrinker *= -1;
	shrinker = (shrinker - 1) * -0.5f + 1;
	height = data->field[x][y];
	x -= data->field_size.x / 2;
	y -= data->field_size.y / 2;
	screen_point.x = data->view_pos.x + data->tile_size
		* (x * cos(data->iso_angle.x)
			+ y * cos(data->iso_angle.y)
			+ height * cos(-90.0f * (M_PI / 180)));
	screen_point.y = data->view_pos.y + data->tile_size
		* (x * sin(data->iso_angle.x) / shrinker
			+ y * sin(data->iso_angle.y) / shrinker
			+ height * sin(-90.0f * (M_PI / 180)));
	return (screen_point);
}

void	drawiso(t_data *data, t_int2 gradient)
{
	t_int2	from;
	t_int2	ind;

	set_int2(&ind, 0, -1);
	set_int2(&data->gradient, gradient.x, gradient.y);
	while (ind.x < data->field_size.x)
	{
		if (++ind.y >= data->field_size.y)
		{
			ind.y = 0;
			if (++ind.x >= data->field_size.x)
				break ;
		}
		from.x = field_to_screen(data, ind.x, ind.y).x;
		from.y = field_to_screen(data, ind.x, ind.y).y;
		if (from.x + data->tile_size < MARGIN || from.x > S_WIDTH - MARGIN
			|| from.y + data->tile_size < MARGIN || from.y > S_HEIGHT - MARGIN)
			continue ;
		if (ind.x + 1 < data->field_size.x)
			drawline(from, field_to_screen(data, ind.x + 1, ind.y),
				data, get_gradient(data, ind.x + 1, ind.y));
		if (ind.y + 1 < data->field_size.y)
			drawline(from, field_to_screen(data, ind.x, ind.y + 1),
				data, get_gradient(data, ind.x, ind.y + 1));
	}
}
