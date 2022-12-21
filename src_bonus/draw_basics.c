/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:01:35 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/20 14:49:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

int	draw_update(t_data *data, void func(t_data *, void *), void *param)
{
	t_int2	black;
	t_int2	gradient;

	if (func)
	{
		set_int2(&black, 0, 0);
		drawiso(data, black);
		func(data, param);
	}
	set_int2(&gradient, 0xFFFFFF, 0xFF0000);
	drawiso(data, gradient);
	render(data);
	return (0);
}

void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	put_pix_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	drawline(t_int2 a, t_int2 b, t_data *data, t_int2 gradient)
{
	t_float2	dir;
	t_float2	pix;
	float		step;
	float		i;

	dir.x = b.x - a.x;
	dir.y = b.y - a.y;
	if (fabs(dir.x) >= fabs(dir.y))
		step = fabs(dir.x);
	else
		step = fabs(dir.y);
	i = 0;
	while (++i <= step)
	{
		pix.x = a.x + (dir.x / step) * i;
		pix.y = a.y + (dir.y / step) * i;
		if (pix.x <= MARGIN || pix.x >= S_WIDTH - MARGIN)
			continue ;
		if (pix.y <= MARGIN || pix.y >= S_HEIGHT - MARGIN)
			continue ;
		put_pix_to_img(data, pix.x, pix.y, tween_color(gradient, i / step));
	}
}
