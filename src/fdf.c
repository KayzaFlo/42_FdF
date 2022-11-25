/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:46:52 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/25 15:43:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int main(int argc, char const *argv[])
{
	t_data		data;
	t_vector2	gradient;

	if (!argc || !argv)
		return (1);
	set_field_from_file(&data, argv[1]);
	gradient.x = 0x00FF00;
	gradient.y = 0xFF0000;
	/* DEBUG */
	for (size_t i = 0; i < 11; i++)
	{
		for (size_t j = 0; j < 19; j++)
		{
			printf("% 4d", data.field[i][j]);
		}
		printf("\n");
	}
	
	/* PARSE FILE */
	set_field_from_file(&data, argv[1]);
	/* PARSE MAP */
	/* SETUP MLX */
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1080, 720, "1080p Window");
	/* DRAW */
	drawarr(&data, gradient);
	/* GET INPUT */
	data.is_clicked = 0;
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, deal_key, (void *)0);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, close_win, (void *)0);
	mlx_hook(data.win_ptr, ON_MOUSEDOWN, 0, deal_mouse, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEMOVE, 0, move_mouse, (void *)&data);
	mlx_hook(data.win_ptr, ON_MOUSEUP, 0, up_mouse, (void *)&data);
	/* LOOP */
	mlx_loop(data.mlx_ptr);
	/* EXIT */
	return (0);
}
