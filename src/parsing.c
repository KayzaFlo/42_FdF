/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/13 15:07:16 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	populate_field_row(t_data *data, int i, char **line)
{
	int		j;
	char	**linearr;

	j = 0;
	linearr = ft_split(*line, ' ');
	free(*line);
	if (!linearr)
		free_and_quit(data, -1);
	data->height.x = 0;
	data->height.y = 0;
	while (j < data->field_size.y)
	{
		data->field[i][j] = ft_atoi(linearr[j]);
		if (data->field[i][j] < data->height.x)
			data->height.x = data->field[i][j];
		if (data->field[i][j] > data->height.y)
			data->height.y = data->field[i][j];
		j++;
	}
	while (j > 0)
		free(linearr[--j]);
	free(linearr);
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
