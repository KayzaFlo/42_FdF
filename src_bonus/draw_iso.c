/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/22 16:18:17 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

static t_int2	get_gradient(t_data *data, t_int2 from, char c)
{
	t_int2	gradient;
	t_int2	to;
	float	height;
	float	maxheight;

	maxheight = data->height.y - data->height.x;
	if (maxheight <= 0)
		maxheight = 1;
	if (c == 'x')
		set_int2(&to, from.x + 1, from.y);
	else if (c == 'y')
		set_int2(&to, from.x, from.y + 1);
	height = data->field[from.x][from.y] - data->height.x;
	gradient.x = tween_color(data->gradient, height / maxheight);
	height = data->field[to.x][to.y] - data->height.x;
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
			+ height * data->amp * cos(-90.0f * (M_PI / 180)));
	screen_point.y = data->view_pos.y + data->tile_size
		* (x * sin(data->iso_angle.x) / shrinker
			+ y * sin(data->iso_angle.y) / shrinker
			+ height * data->amp * sin(-90.0f * (M_PI / 180)));
	return (screen_point);
}

static int	checkdepth(t_data *data, t_int2 *ind)
{
	if (data->view_dir <= 45 || data->view_dir >= 235)
		ind->y = data->field_size.y - 1;
	else
		ind->y = 0;
	if (data->view_dir >= 135 && data->view_dir <= 315)
	{
		if (--ind->x < 0)
			return (1);
	}
	else
	{
		if (++ind->x >= data->field_size.x)
			return (1);
	}
	return (0);
}

static int	drawcol(t_data *data, t_int2 *ind)
{
	t_int2	from;

	if (data->view_dir <= 45 || data->view_dir >= 235)
	{
		if (--ind->y < 0)
			if (checkdepth(data, ind) == 1)
				return (1);
	}
	else
	{
		if (++ind->y >= data->field_size.y)
			if (checkdepth(data, ind) == 1)
				return (1);
	}
	cpy_int2(&from, field_to_screen(data, ind->x, ind->y));
	if (from.x + data->tile_size < MARGIN || from.x > S_WIDTH - MARGIN
		|| from.y + data->tile_size < MARGIN || from.y > S_HEIGHT - MARGIN)
		return (0);
	if (ind->x + 1 < data->field_size.x)
		drawline(from, field_to_screen(data, ind->x + 1, ind->y),
			data, get_gradient(data, *ind, 'x'));
	if (ind->y + 1 < data->field_size.y)
		drawline(from, field_to_screen(data, ind->x, ind->y + 1),
			data, get_gradient(data, *ind, 'y'));
	return (0);
}

void	drawiso(t_data *data, t_int2 gradient)
{
	t_int2	ind;

	if (data->view_dir >= 135 && data->view_dir <= 315)
		ind.x = data->field_size.x - 1;
	else
		ind.x = 0;
	if (data->view_dir <= 45 || data->view_dir >= 235)
		ind.y = data->field_size.y;
	else
		ind.y = -1;
	set_int2(&data->gradient, gradient.x, gradient.y);
	if (data->view_dir >= 135 && data->view_dir <= 315)
	{	
		while (ind.x >= 0)
			if (drawcol(data, &ind) == 1)
				break ;
	}
	else
	{
		while (ind.x < data->field_size.x)
			if (drawcol(data, &ind) == 1)
				break ;
	}
}
