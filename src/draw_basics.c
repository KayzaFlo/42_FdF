/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:01:35 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/13 14:24:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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

void	drawline(t_float2 a, t_float2 b, t_data *data)
{
	t_float2	dir;
	float		step;
	float		i;

	dir.x = b.x - a.x;
	dir.y = b.y - a.y;
	if (fabs(dir.x) >= fabs(dir.y))
		step = fabs(dir.x);
	else
		step = fabs(dir.y);
	dir.x /= step;
	dir.y /= step;
	i = 1;
	while (i <= step)
	{
		if (a.x > 0 && a.x < S_WIDTH && a.y > 0 && a.y < S_HEIGHT)
			put_pix_to_img(data, (int)a.x % S_WIDTH, (int)a.y % S_HEIGHT, 0x00FF00);
		a.x += dir.x;
		a.y += dir.y;
		i += 1;
	}
}
