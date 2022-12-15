/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/15 16:32:55 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
	if (i.x + 1 < data->field_size.x)
	{
		drawto->x = from.x + data->tile_size * cos(data->angle + M_PI / 4);
		drawto->y = from.y + data->tile_size * sin(data->angle + M_PI / 4)
			+ data->tile_size
			* (data->field[i.x][i.y] - data->field[i.x + 1][i.y])
			* sin(data->angle + M_PI / 4);
		drawline(from, *drawto, data);
	}
	if (i.y + 1 < data->field_size.y)
	{
		drawto->x = from.x + data->tile_size * cos(data->angle);
		drawto->y = from.y + data->tile_size * sin(data->angle)
			+ data->tile_size
			* (data->field[i.x][i.y + 1] - data->field[i.x][i.y])
			* sin(data->angle);
		drawline(from, *drawto, data);
	}
}

void	drawiso(t_data *data)
{
	t_int2	from;
	t_int2	to;
	t_int2	ind;

	ind.x = 0;
	ind.y = -1;
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
