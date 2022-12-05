/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:49:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/05 16:47:04 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define S_WIDTH 1920
# define S_HEIGHT 1080

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
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

typedef struct line
{
	t_float2	from;
	t_float2	to;
	t_int2		gradient;
}	t_line;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		is_clicked;
	t_int2	last_click_pos;
	t_int2	view_pos;
	t_int2	view_rot;
	float	zoom;
	float	amp;
	t_int2	height;
	int		**field;
	t_int2	field_size;
	t_int2	gradient;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/* PARSING */
int		set_field_from_file(t_data *data, const char *path);

/* DRAWS */
void	putpiximg(t_data *data, int x, int y, int color);
int		render(void *param);
int		drawline(t_float2 a, t_float2 b, t_data *data, t_int2 gradient);
int		drawiso(t_data *data, t_int2 gradient);

/* INPUTS */
int		i_winclose(void);
int		i_keydown(int key);//, void *param);
int		i_mousedown(int key, int x, int y, void *param);
int		i_mouseup(int key, int x, int y, void *param);
int		i_mousemove(int x, int y, void *param);

/* UPDATES */
int		draw_update(t_data *data, void f(t_data *, void *), void *param);
void	set_movement(t_data *data, void *param);
void	set_zoom(t_data *data, void *param);

/* TWEEN */
int		tween_color(t_int2 gradient, float x);

/* UTILS */
void	set_int2(t_int2 *int2, int a, int b);
void	set_float2(t_float2 *float2, float a, float b);

#endif
