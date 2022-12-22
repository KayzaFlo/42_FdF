/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:45:47 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/22 12:36:01 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

void	translate(t_data *data, void *param)
{
	t_int2	*mouse;

	mouse = (t_int2 *)param;
	data->view_pos.x -= data->last_click_pos.x - mouse->x;
	data->view_pos.y -= data->last_click_pos.y - mouse->y;
	data->last_click_pos.x = mouse->x;
	data->last_click_pos.y = mouse->y;
}

void	rotate(t_data *data, void *param)
{
	t_int2	*mouse;
	float	theta;

	mouse = (t_int2 *)param;
	data->view_dir += (data->last_click_pos.x - mouse->x) * 0.2f;
	if (data->view_dir > 360)
		data->view_dir -= 360;
	else if (data->view_dir < 0)
		data->view_dir += 360;
	theta = (int)data->view_dir % 180 - 90;
	if (theta > 0)
		theta *= -1;
	theta += 135;
	data->iso_angle.x = (data->view_dir + theta / 2) * M_PI / 180;
	data->iso_angle.y = (data->view_dir - theta / 2) * M_PI / 180;
	data->last_click_pos.x = mouse->x;
	data->last_click_pos.y = mouse->y;
}

void	reset(t_data *data, void *param)
{
	data->view_pos.x = S_WIDTH / 2 + (int)param;
	data->view_pos.y = S_HEIGHT / 2 + (int)param;
}

void	zoom(t_data *data, void *param)
{
	float	mult;

	mult = 1 - (data->tile_size - (*(int *)param * 2 - 9)) / data->tile_size;
	data->tile_size -= *(int *)param * 2 - 9;
	if (data->tile_size < 1)
		data->tile_size = 1;
	else
	{
		data->view_pos.x -= (data->view_pos.x - data->last_click_pos.x) * mult;
		data->view_pos.y -= (data->view_pos.y - data->last_click_pos.y) * mult;
	}
}

void	free_and_quit(t_data *data, char *str, int exitcode)
{
	int	i;

	i = 0;
	while (i < data->field_size.x)
	{
		free(data->field[i]);
		i++;
	}
	free(data->field);
	printf("%s (%d)\n", str, exitcode);
	exit (exitcode);
}
