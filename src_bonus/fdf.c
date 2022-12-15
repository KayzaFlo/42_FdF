/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/12 17:39:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_vars(t_data *data, t_int2 *gradient, const char *str)
{
	t_float2	draw_size;

	data->is_clicked = 0;
	data->zoom = 16;
	data->zoom = S_WIDTH / (data->field_size.x + data->field_size.y);
	data->height.x = 0;
	data->height.y = 0;
	data->amp = 1;
	data->filename = (char *)str;
	str = NULL;
	set_int2(gradient, 0xFFFFFF, 0xFF0000);
	set_int2(&data->view_pos, 0, 0);
	draw_size.x = (data->field_size.x + data->field_size.y - 2) * data->zoom;
	data->view_pos.x = S_WIDTH / 2 - draw_size.x / 2;
	draw_size.y = (data->field_size.x - 1) * data->zoom / 2;
	draw_size.y -= (data->field_size.y - 1) * data->zoom / 2;
	data->view_pos.y = S_HEIGHT / 2 - draw_size.y / 2;
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

int	goforloop(void *param)
{
	t_data	*data;

	if (!param)
		return (-1);
	data = (t_data *)param;
	putpiximg(data, 16, 16, rand());
	set_field_from_file(data, data->filename);
	return (0);
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)data);
	// mlx_hook(data->win_ptr, ON_EXPOSE, 0, i_winopen, (void *)data);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, i_winclose, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEDOWN, 0, i_mousedown, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEUP, 0, i_mouseup, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEMOVE, 0, i_mousemove, (void *)data);
	mlx_loop_hook(data->mlx_ptr, goforloop, data);
}

int	main(int argc, char const *argv[])
{
	t_data		data;
	t_int2		gradient;

	if (argc != 2)
		return (-1);
	get_filesize(&data, argv[1]);
	init_vars(&data, &gradient, argv[1]);
	init_mlx(&data);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
