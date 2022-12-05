/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 16:24:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	i_winclose(void)
{
	printf("CLOSED");
	exit(0);
}

int	i_keydown(int key)//, void *param)
{
	if (key == 53)
	{
		printf("ESCAPED");
		exit(0);
	}
	return (0);
}

int	i_mousemove(int x, int y, void *param)
{
	t_data	*data;
	t_int2	mouse;

	data = (t_data *)param;
	set_int2(&mouse, x, y);
	if (data->is_clicked == 1)
		draw_update(data, set_movement, (void *)&mouse);
	return (0);
}

int	i_mouseup(int key, int x, int y, void *param)
{
	t_data		*data;

	if (!param || !x || !y)
		return (-1);
	data = (t_data *)param;
	if (key == 1)
		data->is_clicked = 0;
	return (0);
}

int	i_mousedown(int key, int x, int y, void *param)
{
	t_data	*data;

	if (!param)
		return (-1);
	data = (t_data *)param;
	if (key == 1)
	{
		data->is_clicked = 1;
		set_int2(&data->last_click_pos, x, y);
	}
	if (key == 4 || key == 5)
	{
		set_int2(&data->last_click_pos, x, y);
		draw_update(data, set_zoom, (void *)&key);
	}
	return (0);
}
