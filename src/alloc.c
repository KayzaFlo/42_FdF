/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/13 15:07:22 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	get_wc(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != sep)
			if (str[i + 1] == sep)
				count++;
		i++;
	}
	return (count);
}

static void	alloc_field_rows(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->field_size.x)
	{
		data->field[i] = ft_calloc(data->field_size.y, sizeof(int));
		if (!data->field[i])
			free_and_quit(data, -1);
		i++;
	}
}

void	alloc_field(t_data *data, const char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		printf("Wrong file format!\n");
		exit(-1);
	}
	data->field_size.x = 0;
	data->field_size.y = get_wc(line, ' ');
	while (line)
	{
		data->field_size.x++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->field = ft_calloc(data->field_size.x, sizeof(int *));
	if (!data->field)
		exit(-1);
	alloc_field_rows(data);
	close(fd);
}
