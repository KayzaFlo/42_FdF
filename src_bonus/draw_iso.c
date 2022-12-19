/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/19 14:17:21 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

// static void	set_drawfrom(t_float2 *drawfrom, t_data *data, t_int2 *i)
// {
// 	drawfrom->x = i->x + i->y;
// 	drawfrom->x *= data->zoom;
// 	drawfrom->x += data->view_pos.x;
// 	drawfrom->y = i->x - i->y - data->field[i->x][i->y] * data->amp;
// 	drawfrom->y *= data->zoom / 2;
// 	drawfrom->y += data->view_pos.y;
// }

// static void	set_drawto(t_float2 *drawto, t_data *data, t_int2 i, char next)
// {
// 	if (next == 'x')
// 		i.x++;
// 	if (next == 'y')
// 		i.y++;
// 	drawto->y = i.x - i.y - data->field[i.x][i.y] * data->amp;
// 	drawto->y *= data->zoom / 2;
// 	drawto->y += data->view_pos.y;
// }

static void	set_gradient(t_int2 *gradient, t_data *data, t_int2 i, char next)
{
	float		height;
	float		maxheight;

	maxheight = data->height.y - data->height.x;
	if (maxheight <= 0)
		maxheight = 1;
	if (next == 'x')
		i.x++;
	if (next == 'y')
		i.y++;
	height = data->field[i.x][i.y] - data->height.x;
	gradient->x = tween_color(data->gradient, height / maxheight);
	height = data->field[i.x][i.y] - data->height.x;
	gradient->y = tween_color(data->gradient, height / maxheight);
}

// static void	set_line(t_line *line, t_data *data, t_int2 i)
// {
// 	set_drawfrom(&line->from, data, &i);
// 	line->to.x = line->from.x + data->zoom;
// 	if (i.x + 1 < data->field_size.x)
// 	{
// 		set_drawto(&line->to, data, i, 'x');
// 		set_gradient(&line->gradient, data, i, 'x');
// 		drawline(line->from, line->to, data, line->gradient);
// 	}
// 	if (i.y + 1 < data->field_size.y)
// 	{
// 		set_drawto(&line->to, data, i, 'y');
// 		set_gradient(&line->gradient, data, i, 'y');
// 		drawline(line->from, line->to, data, line->gradient);
// 	}
// }

static void	set_linefrom(t_int2 *drawfrom, t_data *data, t_int2 i)
{
	float	angle;
	int		nextheight;

	nextheight = data->field[i.x][i.y] - data->field[0][0];
	angle = data->angle;
	i.x -= data->field_size.x / 2;
	i.y -= data->field_size.y / 2;
	drawfrom->x = data->view_pos.x + data->tile_size
		* (i.x * cos(angle + M_PI / 4) + i.y * cos(angle));
	drawfrom->y = data->view_pos.y + data->tile_size
		* (-i.x * sin(angle)
			+ i.y * sin(angle)
			+ nextheight * sin(angle));
}

static void	draw_lineto(t_int2 *drawto, t_data *data, t_int2 i, t_int2 from)
{
	t_int2	grad;

	if (i.x + 1 < data->field_size.x)
	{
		drawto->x = from.x + data->tile_size * cos(data->angle + M_PI / 4);
		drawto->y = from.y + data->tile_size * sin(data->angle + M_PI / 4)
			+ data->tile_size
			* (data->field[i.x][i.y] - data->field[i.x + 1][i.y])
			* sin(data->angle + M_PI / 4);
		set_gradient(&grad, data, i, 'x');
		drawline(from, *drawto, data, grad);
	}
	if (i.y + 1 < data->field_size.y)
	{
		drawto->x = from.x + data->tile_size * cos(data->angle);
		drawto->y = from.y + data->tile_size * sin(data->angle)
			+ data->tile_size
			* (data->field[i.x][i.y + 1] - data->field[i.x][i.y])
			* sin(data->angle);
		set_gradient(&grad, data, i, 'y');
		drawline(from, *drawto, data, grad);
	}
}

void	drawiso(t_data *data, t_int2 gradient)
{
	t_int2	from;
	t_int2	to;
	t_int2	ind;

 	set_int2(&ind, 0, -1);
 	set_int2(&data->gradient, gradient.x, gradient.y);
	while (ind.x < data->field_size.x)
	{
		if (++ind.y >= data->field_size.y)
		{
			ind.y = 0;
			ind.x++;
			if (ind.x >= data->field_size.x)
				break ;
		}
		set_linefrom(&from, data, ind);
		if (from.x + data->tile_size < MARGIN || from.x > S_WIDTH - MARGIN)
			continue ;
		if (from.y + data->tile_size < MARGIN || from.y > S_HEIGHT - MARGIN)
			continue ;
		draw_lineto(&to, data, ind, from);
	}
	render((void *)data);
}

// int	drawiso(t_data *data, t_int2 gradient)
// {
// 	t_line		line;
// 	t_int2		i;

// 	set_int2(&i, 0, 0);
// 	set_int2(&data->gradient, gradient.x, gradient.y);
// 	while (i.x < data->field_size.x)
// 	{
// 		set_line(&line, data, i);
// 		if (++i.y >= data->field_size.y)
// 		{
// 			i.y = 0;
// 			i.x++;
// 		}
// 	}
// 	render((void *)data);
// 	return (0);
// }