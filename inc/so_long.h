/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:49:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/25 15:44:35 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include "../libft/libft.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_mlxrefs
{
	void		*mlx_ptr;
	void		*win_ptr;
}	t_mlxrefs;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			is_clicked;
	t_vector2	last_click_pos;
	t_vector2	view_pos;
	t_vector2	view_rot;
	t_vector2	rangeheight;
	int			**field;
	t_vector2	field_size;
}	t_data;

int	set_field_from_file(t_data *data, const char *path);

int	drawline(t_vector2 startpos, t_vector2 endpos, t_data *data, t_vector2 gradient);
int	drawarr(t_data *data, t_vector2 gradient);

int	close_win(void);
int	deal_key(int key, void *param);
int	deal_mouse(int key, int x, int y, void *param);
int	up_mouse(int key, int x, int y, void *param);
int	move_mouse(int x, int y, void *param);

#endif
