/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 17:35:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	set_drawfrom(t_float2 *drawfrom, t_data *data, t_int2 *i)
{
	drawfrom->x = i->x + i->y;
	drawfrom->x *= data->zoom;
	drawfrom->x += data->view_pos.x;
	drawfrom->y = i->x - i->y - data->field[i->x][i->y] * data->amp;
	drawfrom->y *= data->zoom / 2;
	drawfrom->y += data->view_pos.y;
}

static void	set_drawto(t_float2 *drawto, t_data *data, t_int2 i, char next)
{
	if (next == 'x')
		i.x++;
	if (next == 'y')
		i.y++;
	drawto->y = i.x - i.y - data->field[i.x][i.y] * data->amp;
	drawto->y *= data->zoom / 2;
	drawto->y += data->view_pos.y;
}

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

static void	set_line(t_line *line, t_data *data, t_int2 i)
{
	set_drawfrom(&line->from, data, &i);
	line->to.x = line->from.x + data->zoom;
	if (i.x + 1 < data->field_size.x)
	{
		set_drawto(&line->to, data, i, 'x');
		set_gradient(&line->gradient, data, i, 'x');
		drawline(line->from, line->to, data, line->gradient);
	}
	if (i.y + 1 < data->field_size.y)
	{
		set_drawto(&line->to, data, i, 'y');
		set_gradient(&line->gradient, data, i, 'y');
		drawline(line->from, line->to, data, line->gradient);
	}
}

int	drawiso(t_data *data, t_int2 gradient)
{
	t_line		line;
	t_int2		i;

	set_int2(&i, 0, 0);
	set_int2(&data->gradient, gradient.x, gradient.y);
	while (i.x < data->field_size.x)
	{
		set_line(&line, data, i);
		if (++i.y == data->field_size.x)
		{
			i.y = 0;
			i.x++;
		}
	}
	render((void *)data);
	return (0);
}
