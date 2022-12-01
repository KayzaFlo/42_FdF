/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:45:47 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/01 13:20:33 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	draw_update(t_data *data, void f(t_data *, void *), void *param)
{
	t_int2	gradient = {0xFFFFFF, 0xFF0000};
	t_int2	black = {0, 0};

	drawarr(data, black);
	f(data, param);
	drawarr(data, gradient);
	return (0);
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

void	set_zoom(t_data *data, void *param)
{
	data->zoom -= *(int *)param * 2 - 9;
}
