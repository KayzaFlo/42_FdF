/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/28 12:57:36 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	debugparse(t_data *data)
{
	for (size_t i = 0; i < 11; i++)
	{
		for (size_t j = 0; j < 19; j++)
		{
			printf("% 4d", data->field[i][j]);
		}
		printf("\n");
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_data		data;
	t_int2		gradient = {0x00FF00, 0xFF0000};

	if (argc != 2)
		return (-1);
	/* SET DATA VAR */
	data.is_clicked = 0;
	data.zoom = 32;
	/* PARSE FILE */
	set_field_from_file(&data, argv[1]);
	/* DEBUG */	debugparse(&data);
	/* SETUP MLX */
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1080, 720, "1080p Window");
	/* DRAW */
	drawarr(&data, gradient);
	/* GET INPUT */
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, i_keydown, (void *)0);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, i_winclose, (void *)0);
	mlx_hook(data.win_ptr, ON_MOUSEDOWN, 0, i_mousedown, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEUP, 0, i_mouseup, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEMOVE, 0, i_mousemove, (void *)&data);
	/* LOOP */
	mlx_loop(data.mlx_ptr);
	/* EXIT */
	return (0);
}
