/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/15 15:18:14 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	populate_field_row(t_data *data, int i, char **line)
{
	int		j;
	char	**line_split;

	j = -1;
	line_split = ft_split(*line, ' ');
	free(*line);
	if (!line_split)
		free_and_quit(data, -1);
	data->height.x = 0;
	data->height.y = 0;
	while (++j < data->field_size.y)
	{
		data->field[i][j] = ft_atoi(line_split[j]);
		if (data->field[i][j] < data->height.x)
			data->height.x = data->field[i][j];
		if (data->field[i][j] > data->height.y)
			data->height.y = data->field[i][j];
	}
	while (line_split[j])
		j++;
	while (j > 0)
		free(line_split[--j]);
	free(line_split);
}

void	set_field_from_file(t_data *data, const char *path)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		free_and_quit(data, -1);
	}
	i = 0;
	while (line)
	{
		populate_field_row(data, i, &line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
