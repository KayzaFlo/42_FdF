/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/25 15:43:58 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

int	set_field_from_file(t_data *data, const char *path)
{
	t_vector2	ind;
	int			fd;
	char		*line;
	char		**linearr;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	data->field_size.x = 0;
	data->field_size.y = get_wc(line, ' ') + 1;
	while(line)
	{
		data->field_size.x++;
		line = get_next_line(fd);
	}
	data->field = ft_calloc(data->field_size.x, sizeof(int*));
	ind.y = 0;
	while (ind.y < data->field_size.y)
	{
		data->field[ind.y] = ft_calloc(data->field_size.y, sizeof(int));
		ind.y++;
	}
	printf("x: %d, y: %d\n", data->field_size.x, data->field_size.y);
	close(fd);

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	ind.y = 0;
	while(line)
	{
		ind.x = 0;
		linearr = ft_split(line, ' ');
		while (linearr[ind.x])
		{
			data->field[ind.y][ind.x] = ft_atoi(linearr[ind.x]);
			if (data->field[ind.y][ind.x] < data->rangeheight.x)
				data->rangeheight.x = data->field[ind.y][ind.x];
			if (data->field[ind.y][ind.x] > data->rangeheight.y)
				data->rangeheight.y = data->field[ind.y][ind.x];
			ind.x++;
		}
		ind.y++;
		free(linearr);
		line = get_next_line(fd);
	}
	close(fd);
	return(0);
}
