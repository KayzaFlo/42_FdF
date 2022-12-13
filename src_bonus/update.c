/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:45:47 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/12 17:34:04 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	draw_update(t_data *data, void func(t_data *, void *), void *param)
{
	t_int2	black;
	t_int2	gradient;

	set_int2(&black, 0, 0);
	drawiso(data, black);
	if (func)
		func(data, param);
	set_int2(&gradient, 0xFFFFFF, 0xFF0000);
	drawiso(data, gradient);
	return (0);
}

void	paintcanvas(t_data *data, void *param)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < S_WIDTH)
	{
		j = 0;
		while (j < S_HEIGHT)
		{
			putpiximg(data, i, j, (int)param);
			j++;
		}
		i++;
	}
}

void	set_movement(t_data *data, void *param)
{
	t_int2	*mouse;

	mouse = (t_int2 *)param;
	data->view_pos.x -= data->last_click_pos.x - mouse->x;
	data->view_pos.y -= data->last_click_pos.y - mouse->y;
	data->last_click_pos.x = mouse->x;
	data->last_click_pos.y = mouse->y;
}

void	reset_pos(t_data *data, void *param)
{
	t_float2	draw_size;

	draw_size.x = (data->field_size.x + data->field_size.y - 2) * data->zoom;
	data->view_pos.x = S_WIDTH / 2 - draw_size.x / 2 + (int)param;
	draw_size.y = (data->field_size.x - 1) * data->zoom / 2;
	draw_size.y -= (data->field_size.y - 1) * data->zoom / 2;
	data->view_pos.y = S_HEIGHT / 2 - draw_size.y / 2 + (int)param;
}

void	set_zoom(t_data *data, void *param)
{
	float	mult;

	mult = 1 - (data->zoom - (*(int *)param * 2 - 9)) / data->zoom;
	data->zoom -= *(int *)param * 2 - 9;
	if (data->zoom < 1)
		data->zoom = 1;
	else
	{
		data->view_pos.x -= (data->view_pos.x - data->last_click_pos.x) * mult;
		data->view_pos.y -= (data->view_pos.y - data->last_click_pos.y) * mult;
	}
}

void	free_and_quit(t_data *data, int exitcode)
{
	int	i;

	i = 0;
	while (i < data->field_size.x)
	{
		free(data->field[i]);
		i++;
	}
	free(data->field);
	exit (exitcode);
}
