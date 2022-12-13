/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:01:35 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 16:14:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

void	putpiximg(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	drawline(t_float2 a, t_float2 b, t_data *data, t_int2 gradient)
{
	t_float2	dir;
	float		step;
	float		i;
	int			color;

	set_float2(&dir, b.x - a.x, b.y - a.y);
	if (fabs(dir.x) >= fabs(dir.y))
		step = fabs(dir.x);
	else
		step = fabs(dir.y);
	set_float2(&dir, dir.x / step, dir.y / step);
	i = 1;
	while (i <= step)
	{
		color = tween_color(gradient, i / step);
		if (a.x > 64 && a.x < S_WIDTH - 64 && a.y > 64 && a.y < S_HEIGHT - 64)
			putpiximg(data, (int)a.x % S_WIDTH, (int)a.y % S_HEIGHT, color);
		set_float2(&a, a.x + dir.x, a.y + dir.y);
		i += 1;
	}
	return (0);
}
