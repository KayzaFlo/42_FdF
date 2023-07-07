/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:49:57 by fgeslin           #+#    #+#             */
/*   Updated: 2023/07/07 11:14:55 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define S_WIDTH 1920
# define S_HEIGHT 1080
# define MARGIN 32

enum e_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_CREATE = 16,
	ON_DESTROY = 17
};

typedef struct s_int2
{
	int	x;
	int	y;
}	t_int2;

typedef struct s_float2
{
	float	x;
	float	y;
}	t_float2;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;

	t_int2	view_pos;
	float	tile_size;
	t_int2	height;
	int		**field;
	t_int2	field_size;
	float	angle;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/* PARSING */
void	alloc_field(t_data *data, const char *path);
void	set_field_from_file(t_data *data, const char *path);

/* DRAWS */
void	put_pix_to_img(t_data *data, int x, int y, int color);
void	render(void *param);
void	drawline(t_int2 a, t_int2 b, t_data *data);
void	drawiso(t_data *data);

/* INPUTS */
int		i_winclose(void *param);
int		i_keydown(int key, void *param);

void	free_and_quit(t_data *data, int exitcode);

#endif
