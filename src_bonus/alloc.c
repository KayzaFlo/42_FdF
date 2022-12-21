/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:43 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/21 18:15:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

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
		if (str[i] != sep && str[i] != '\n')
		{
			if (str[i + 1] == sep)
				count++;
			else if (str[i + 1] == '\0')
				count++;
			else if (str[i + 1] == '\n')
				count++;
		}
		i++;
	}
	return (count);
}

static void	set_field_size(t_data *data, const char *path)
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
	close(fd);
}

void	alloc_field(t_data *data, const char *path)
{
	int	i;

	set_field_size(data, path);
	data->field = ft_calloc(data->field_size.x, sizeof(int *));
	if (!data->field)
		exit(-1);
	i = 0;
	while (i < data->field_size.x)
	{
		data->field[i] = ft_calloc(data->field_size.y, sizeof(int));
		if (!data->field[i])
			free_and_quit(data, -1);
		i++;
	}
}
