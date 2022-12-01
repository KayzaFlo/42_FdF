/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/11/29 14:50:32 by fgeslin          ###   ########.fr       */
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

int	set_field_from_file(t_data *data, const char *path)
{
	t_int2	ind;
	int		fd;
	char	*line;
	char	**linearr;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	data->field_size.x = 0; //rows
	data->field_size.y = get_wc(line, ' ') + 1; //cols
	while (line)
	{
		data->field_size.x++;
		line = get_next_line(fd);
	}
	data->field = ft_calloc(data->field_size.x, sizeof(int *));
	ind.x = 0;
	while (ind.x < data->field_size.x)
	{
		data->field[ind.x] = ft_calloc(data->field_size.y, sizeof(int));
		ind.x++;
	}
	printf("x: %d, y: %d\n", data->field_size.x, data->field_size.y); /* DEBUG */
	close(fd);

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	ind.x = 0;
	data->rangeheight.x = 0;
	data->rangeheight.y = 0;
	while (line)
	{
		ind.y = 0;
		linearr = ft_split(line, ' ');
		while (linearr[ind.y])
		{
			data->field[ind.x][ind.y] = ft_atoi(linearr[ind.y]);
			if (data->field[ind.x][ind.y] < data->rangeheight.x)
				data->rangeheight.x = data->field[ind.x][ind.y];
			if (data->field[ind.x][ind.y] > data->rangeheight.y)
				data->rangeheight.y = data->field[ind.x][ind.y];
			ind.y++;
		}
		ind.x++;
		free(linearr);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
