/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 16:44:57 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_vars(t_data *data, t_int2 *gradient)
{
	data->is_clicked = 0;
	data->zoom = 16;
	data->amp = 1;
	set_int2(gradient, 0xFFFFFF, 0xFF0000);
	set_int2(&data->view_pos, 0, 0);
}

static void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, S_WIDTH, S_HEIGHT, "FdF");
	data->img = mlx_new_image(data->mlx_ptr, S_WIDTH, S_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
								&data->line_length, &data->endian);
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)0);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, i_winclose, (void *)0);
	mlx_hook(data->win_ptr, ON_MOUSEDOWN, 0, i_mousedown, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEUP, 0, i_mouseup, (void *)data);
	mlx_hook(data->win_ptr, ON_MOUSEMOVE, 0, i_mousemove, (void *)data);
}

int	main(int argc, char const *argv[])
{
	t_data		data;
	t_int2		gradient;

	if (argc != 2)
		return (-1);
	init_vars(&data, &gradient);
	set_field_from_file(&data, argv[1]);
	init_mlx(&data);
	drawiso(&data, gradient);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
