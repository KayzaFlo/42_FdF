/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/15 16:30:34 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_vars(t_data *data)
{
	t_float2	draw_size;

	data->angle = M_PI / -8.0f;
	draw_size.x = (float)(S_WIDTH - MARGIN)
		/ (float)(data->field_size.x + data->field_size.y);
	draw_size.y = (float)(S_HEIGHT - MARGIN)
		/ (float)((data->field_size.x + data->field_size.y
				+ data->height.y - data->height.x) / 2);
	if (draw_size.x < draw_size.y)
		data->tile_size = draw_size.x;
	else
		data->tile_size = draw_size.y;
	data->view_pos.x = S_WIDTH / 2;
	data->view_pos.y = S_HEIGHT / 2;
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

int	main(int argc, char const *argv[])
{
	t_data		data;

	if (argc != 2 && argv)
		return (-1);
	alloc_field(&data, argv[1]);
	init_mlx(&data);
	set_field_from_file(&data, argv[1]);
	init_vars(&data);
	drawiso(&data);
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)&data);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, i_winclose, (void *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
