/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/29 13:03:00 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	i_winclose(void)
{
	printf("CLOSED");
	exit(0);
}

int	i_keydown(int key, void *param)
{
	printf("X%p", param);
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
	mouse.x = x;
	mouse.y = y;
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
	printf("mouseup%d\n", key);
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
		data->last_click_pos.x = x;
		data->last_click_pos.y = y;
	}
	if (key == 4 || key == 5)
		draw_update(data, set_zoom, (void *)&key);
	printf("mousedown%d\n", key);
	return (0);
}
