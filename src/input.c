/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/25 15:43:09 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_win(void)
{
	printf("CLOSED");
	exit(0);
}

int	deal_key(int key, void *param)
{
	printf("X%p", param);
	if (key == 53)
	{
		printf("ESCAPED");
		exit(0);
	}
	return (0);
}

int	move_mouse(int x, int y, void *param)
{
	t_data		*data;
	t_vector2	gradient;
	t_vector2	black;

	gradient.x = 0x00FF00;
	gradient.y = 0xFF0000;
	black.x = 0x000000;
	black.y = 0x000000;
	data = (t_data *)param;
	if (data->is_clicked == 1)
	{
		drawarr(data, black);
		data->view_pos.x -= data->last_click_pos.x - x;
		data->view_pos.y -= data->last_click_pos.y - y;
		data->last_click_pos.x = x;
		data->last_click_pos.y = y;
		drawarr(data, gradient);
	// printf("viewpos %d %d\n", data->view_pos.x, data->view_pos.y);
	}
	return (0);
}

int	up_mouse(int key, int x, int y, void *param)
{
	t_data		*data;
	t_vector2	clickpos;

	if (!param)
		return (-1);
	clickpos.x = x;
	clickpos.y = y;
	data = (t_data *)param;
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00FFFF);
	data->is_clicked = 0;
	printf("mouseup%d\n", key);
	return (0);
}

int	deal_mouse(int key, int x, int y, void *param)
{
	t_data		*data;
	t_vector2	clickpos;

	if (!param)
		return (-1);
	clickpos.x = x;
	clickpos.y = y;
	data = (t_data *)param;
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x0000FF);
	data->is_clicked = 1;
	data->last_click_pos.x = x;
	data->last_click_pos.y = y;
	printf("mousedown%d\n", key);
	return (0);
}
