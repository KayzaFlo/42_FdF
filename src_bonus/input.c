/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2023/01/04 12:43:38 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

int	i_winclose(void *param)
{
	free_and_quit((t_data *)param, "Win close", 0);
	return (0);
}

int	i_keydown(int key, void *param)
{
	t_data	*data;

	if (!param)
		return (-1);
	data = (t_data *)param;
	if (key == 53)
		free_and_quit(data, "Escape", 0);
	if (key == 49)
		draw_update(data, reset, (void *) 0);
	if (key == 69)
		draw_update(data, amp, (void *) &key);
	if (key == 78)
		draw_update(data, amp, (void *) &key);
	return (0);
}

int	i_mousemove(int x, int y, void *param)
{
	t_data	*data;
	t_int2	mouse;

	data = (t_data *)param;
	set_int2(&mouse, x, y);
	if (data->is_clicked == 1)
		draw_update(data, translate, (void *)&mouse);
	if (data->is_clicked == 2)
		draw_update(data, rotate, (void *)&mouse);
	return (0);
}

int	i_mouseup(int key, int x, int y, void *param)
{
	t_data		*data;

	if (!param || !x || !y)
		return (-1);
	data = (t_data *)param;
	if (key == 1 || key == 2)
		data->is_clicked = 0;
	return (0);
}

int	i_mousedown(int key, int x, int y, void *param)
{
	t_data	*data;

	if (!param)
		return (-1);
	data = (t_data *)param;
	if (key == 1 && x >= 0 && y >= 0)
	{
		data->is_clicked = 1;
		set_int2(&data->last_click_pos, x, y);
	}
	if (key == 2 && x >= 0 && y >= 0)
	{
		data->is_clicked = 2;
		set_int2(&data->last_click_pos, x, y);
	}
	if (key == 4 || key == 5)
	{
		set_int2(&data->last_click_pos, x, y);
		draw_update(data, zoom, (void *)&key);
	}
	return (0);
}
