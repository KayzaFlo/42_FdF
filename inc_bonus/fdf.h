/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:49:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/22 12:21:42 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
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

typedef struct line
{
	t_float2	from;
	t_float2	to;
	t_int2		gradient;
}	t_line;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;

	int			is_clicked;
	t_int2		last_click_pos;
	t_int2		view_pos;
	float		view_dir;
	t_float2	iso_angle;
	float		tile_size;
	float		amp;
	t_int2		height;
	int			**field;
	t_int2		field_size;
	t_int2		gradient;
	char		*filepath;

	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_data;

/* PARSING */
void	alloc_field(t_data *data, const char *path);
int		loop_parsedraw(void *param);

/* DRAWS */
void	put_pix_to_img(t_data *data, int x, int y, int color);
void	render(void *param);
void	drawline(t_int2 a, t_int2 b, t_data *data, t_int2 gradient);
void	drawiso(t_data *data, t_int2 gradient);

/* INPUTS */
int		i_winclose(void *param);
int		i_keydown(int key, void *param);
int		i_mousedown(int key, int x, int y, void *param);
int		i_mouseup(int key, int x, int y, void *param);
int		i_mousemove(int x, int y, void *param);

/* UPDATES */
int		draw_update(t_data *data, void f(t_data *, void *), void *param);
void	translate(t_data *data, void *param);
void	rotate(t_data *data, void *param);
void	reset(t_data *data, void *param);
void	zoom(t_data *data, void *param);
void	free_and_quit(t_data *data, char *str, int exitcode);

/* TWEEN */
int		tween_color(t_int2 gradient, float x);

/* UTILS */
void	set_int2(t_int2 *int2, int a, int b);
void	set_float2(t_float2 *float2, float a, float b);

#endif
