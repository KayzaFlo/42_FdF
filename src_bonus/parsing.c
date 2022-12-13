/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/12 17:44:25 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	get_wc(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep)
			if (str[i + 1] == sep)
				count++;
		i++;
	}
	return (count);
}

int	get_filesize(t_data *data, const char *path)
{
	t_int2	ind;
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(-1);
	data->field_size.x = 0;
	data->field_size.y = get_wc(line, ' ') + 1;
	while (line)
	{
		data->field_size.x++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->field = ft_calloc(data->field_size.x, sizeof(int *));
	ind.x = 0;
	while (ind.x < data->field_size.x)
	{
		data->field[ind.x] = ft_calloc(data->field_size.y, sizeof(int));
		ind.x++;
	}
	close(fd);
	return (0);
}

int	set_field_from_file(t_data *data, const char *path)
{
	static int	i = 0;
	static int	j = 0;
	static int	fd = 0;
	static char	*line = NULL;
	static char	**linearr = NULL;

	if (!fd)
		fd = open(path, O_RDONLY);
	if (!line)
		line = get_next_line(fd);
	if (!line)
		return (-1);
	if (!linearr)
		linearr = ft_split(line, ' ');
	if (!linearr)
		return (-1);
	while (linearr[j])
	{
		data->field[i][j] = ft_atoi(linearr[j]);
		if (data->field[i][j] < data->height.x)
			data->height.x = data->field[i][j];
		if (data->field[i][j] > data->height.y)
			data->height.y = data->field[i][j];
		j++;
	}
	i++;
	while (j > 0)
		free(linearr[--j]);
	free(linearr);
	linearr = NULL;
	free(line);
	line = get_next_line(fd);
	draw_update(data, paintcanvas, 0);
	if (!line)
	{
		free(line);
		close(fd);
		return (1);
	}
	return (0);
}

// int	set_field_from_file(t_data *data, const char *path)
// {
// 	t_int2	ind;
// 	int		fd;
// 	char	*line;
// 	char	**linearr;

// 	fd = open(path, O_RDONLY);
// 	line = get_next_line(fd);
// 	if (!line)
// 		free_and_quit(data, -1);
// 	ind.x = 0;
// 	while (line)
// 	{
// 		ind.y = 0;
// 		linearr = ft_split(line, ' ');
// 		if (!linearr)
// 			free_and_quit(data, -1);
// 		while (linearr[ind.y])
// 		{
// 			data->field[ind.x][ind.y] = ft_atoi(linearr[ind.y]);
// 			if (data->field[ind.x][ind.y] < data->height.x)
// 				data->height.x = data->field[ind.x][ind.y];
// 			if (data->field[ind.x][ind.y] > data->height.y)
// 				data->height.y = data->field[ind.x][ind.y];
// 			ind.y++;
// 		}
// 		ind.x++;
// 		while (ind.y > 0)
// 			free(linearr[--ind.y]);
// 		free(linearr);
// 		free(line);
// 		line = get_next_line(fd);

// 		putpiximg(data, ind.x, ind.y, 0xFF0000);
// 		render(data);
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }
