/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_iso.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:03:20 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/13 13:56:00 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	set_drawfrom(t_float2 *drawfrom, t_data *data, t_int2 *i)
{
	drawfrom->x = (i->x + i->y)
		* data->tile_size
		+ data->view_pos.x;
	drawfrom->y = (i->x - i->y - data->field[i->x][i->y])
		* data->tile_size / 2
		+ data->view_pos.y;
}

static void	set_drawto(t_float2 *drawto, t_data *data, t_int2 i, char next)
{
	if (next == 'x')
		i.x++;
	if (next == 'y')
		i.y++;
	drawto->y = (i.x - i.y - data->field[i.x][i.y])
		* data->tile_size / 2
		+ data->view_pos.y;
}

static void	set_line(t_float2 *from, t_float2 *to, t_data *data, t_int2 i)
{
	set_drawfrom(from, data, &i);
	to->x = from->x + data->tile_size;
	if (i.x + 1 < data->field_size.x)
	{
		set_drawto(to, data, i, 'x');
		drawline(*from, *to, data);
	}
	if (i.y + 1 < data->field_size.y)
	{
		set_drawto(to, data, i, 'y');
		drawline(*from, *to, data);
	}
}

void	drawiso(t_data *data)
{
	t_float2	from;
	t_float2	to;
	t_int2		i;

	i.x = 0;
	i.y = 0;
	while (i.x < data->field_size.x)
	{
		set_line(&from, &to, data, i);
		if (++i.y >= data->field_size.y)
		{
			i.y = 0;
			i.x++;
		}
	}
	render((void *)data);
}
