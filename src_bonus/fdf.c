/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/22 16:04:04 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

static void	init_vars(t_data *data, const char *str)
{
	t_float2	draw_size;

	data->is_clicked = 0;
	data->height.x = 0;
	data->height.y = 0;
	data->amp = 1.0f;
	data->filepath = (char *)str;
	set_int2(&data->view_pos, S_WIDTH / 2, S_HEIGHT / 2);
	data->view_dir = 0;
	rotate(data, (void *)&data->height);
	draw_size.x = (float)(S_WIDTH - MARGIN)
		/ (float)(data->field_size.x + data->field_size.y);
	draw_size.y = (float)(S_HEIGHT - MARGIN)
		/ (float)((data->field_size.x + data->field_size.y
				+ data->height.y - data->height.x) / 2);
	if (draw_size.x < draw_size.y)
		data->tile_size = draw_size.x;
	else
		data->tile_size = draw_size.y;
}

static void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, S_WIDTH, S_HEIGHT, "FdF");
	if (!data->win_ptr)
		exit (-1);
	data->img = mlx_new_image(data->mlx_ptr, S_WIDTH, S_HEIGHT);
	if (!data->img)
		exit (-1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		exit (-1);
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)data);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, i_winclose, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEDOWN, 0, i_mousedown, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEUP, 0, i_mouseup, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEMOVE, 0, i_mousemove, (void *)data);
	mlx_loop_hook(data->mlx_ptr, loop_parsedraw, data);
}

int	main(int argc, char const *argv[])
{
	t_data		data;

	if (argc != 2)
		return (-1);
	alloc_field(&data, argv[1]);
	init_mlx(&data);
	init_vars(&data, argv[1]);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
