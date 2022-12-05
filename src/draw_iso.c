/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 15:08:15 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	set_drawfrom(t_float2 *drawfrom, t_data *data, t_int2 *i)
{
	drawfrom->x = i->x * data->zoom + i->y * data->zoom;
	drawfrom->x += data->view_pos.x + S_WIDTH / 2;
	drawfrom->y = i->x * data->zoom / 2;
	drawfrom->y -= (i->y + data->field[i->x][i->y] * data->amp) * data->zoom / 2;
	drawfrom->y += data->view_pos.y + S_HEIGHT / 2;
}

static void	set_drawto(t_float2 *drawto, t_data *data, t_int2 i, char next)
{
	if (next == 'x')
		i.x++;
	if (next == 'y')
		i.y++;
	drawto->y = (i.x) * data->zoom / 2;
	drawto->y -= (i.y + data->field[i.x][i.y] * data->amp) * data->zoom / 2;
	drawto->y += data->view_pos.y + S_HEIGHT / 2;
}

static void	set_gradient(t_int2 *grad, t_data *data, t_int2 i, char next, t_int2 gradient)
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
	grad->x = tween_color(gradient, height / maxheight);
	height = data->field[i.x][i.y] - data->height.x;
	grad->y = tween_color(gradient, height / maxheight);
}

int	drawiso(t_data *data, t_int2 gradient)
{
	t_float2	drawfrom;
	t_float2	drawto;
	t_int2		i;
	t_int2		grad;

	i.x = 0;
	i.y = 0;
	while (i.x < data->field_size.x)
	{
		set_drawfrom(&drawfrom, data, &i);
		drawto.x = drawfrom.x + data->zoom;
		if (i.x + 1 < data->field_size.x)
		{
			set_drawto(&drawto, data, i, 'x');
			set_gradient(&grad, data, i, 'x', gradient);
			drawline(drawfrom, drawto, data, grad);
		}
		if (i.y + 1 < data->field_size.y)
		{
			set_drawto(&drawto, data, i, 'y');
			set_gradient(&grad, data, i, 'y', gradient);
			drawline(drawfrom, drawto, data, grad);
		}
		if (++i.y == data->field_size.x)
		{
			i.y = 0;
			i.x++;
		}
	}
	render((void *)data);
	return (0);
}
