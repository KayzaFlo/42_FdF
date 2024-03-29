/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/22 16:15:31 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

static void	populate_field_row(t_data *data, int i, char **line)
{
	int		j;
	int		n;
	char	**line_split;

	line_split = ft_split(*line, ' ');
	free(*line);
	if (!line_split)
		free_and_quit(data, "populate_field_row: Wrong file format!", -1);
	n = 0;
	while (line_split[n])
		n++;
	if (n < data->field_size.y)
		free_and_quit(data, "populate_field_row: Wrong file format!", -1);
	j = -1;
	while (++j < data->field_size.y)
	{
		data->field[i][j] = ft_atoi(line_split[j]);
		if (data->field[i][j] < data->height.x)
			data->height.x = data->field[i][j];
		if (data->field[i][j] > data->height.y)
			data->height.y = data->field[i][j];
	}
	while (n > 0)
		free(line_split[--n]);
	free(line_split);
}

static void	set_field_from_file(t_data *data, void *param)
{
	static int	i = 0;
	static int	fd = 0;
	static char	*line = 0;
	int			loop;

	loop = *(int *)param;
	while (loop > 0)
	{
		if (!fd)
			fd = open(data->filepath, O_RDONLY);
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return ;
		}
		populate_field_row(data, i, &line);
		if (++i == data->field_size.x)
			close(fd);
		loop--;
	}
}

int	loop_parsedraw(void *param)
{
	t_data		*data;
	static int	coldrawn = -1;
	int			draw_freq;

	draw_freq = 20;
	if (!param)
		return (-1);
	data = (t_data *)param;
	if (coldrawn == -1)
	{
		draw_update(data, 0, (void *) 0);
		coldrawn = 0;
	}
	else if (coldrawn < data->field_size.x)
	{
		if (data->field_size.x - coldrawn < draw_freq)
			draw_freq = data->field_size.x - coldrawn;
		draw_update(data, set_field_from_file, (void *)&draw_freq);
		coldrawn += draw_freq;
	}
	return (0);
}
