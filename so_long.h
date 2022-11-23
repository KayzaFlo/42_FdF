/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:49:57 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/23 14:41:13 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
// #include "../libft/libft.h"

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_mlxrefs
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_vector2	lastclick;
}	t_mlxrefs;

int	drawline(t_vector2 startpos, t_vector2 endpos, t_mlxrefs *mlxrefs);

#endif
