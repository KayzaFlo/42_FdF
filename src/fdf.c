/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/29 15:25:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char const *argv[])
{
	t_data		data;
	t_int2		gradient = {0x00FF00, 0xFF0000};

	if (argc != 2)
		return (-1);
	/* SET DATA VAR */
	data.is_clicked = 0;
	data.zoom = 16;
	/* PARSE FILE */
	set_field_from_file(&data, argv[1]);
	/* SETUP MLX */
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, S_WIDTH, S_HEIGHT, "FdF");
	data.img = mlx_new_image(data.mlx_ptr, S_WIDTH, S_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
								&data.line_length, &data.endian);
	/* DRAW */
	drawarr(&data, gradient);
	/* GET INPUT */
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)0);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, i_winclose, (void *)0);
	mlx_hook(data.win_ptr, ON_MOUSEDOWN, 0, i_mousedown, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEUP, 0, i_mouseup, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEMOVE, 0, i_mousemove, (void *)&data);
	// mlx_loop_hook(data.mlx_ptr, render, (void *)&data);
	/* LOOP */
	mlx_loop(data.mlx_ptr);
	/* EXIT */
	return (0);
}
