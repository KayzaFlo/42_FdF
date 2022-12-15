/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/15 13:27:40 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_and_quit(t_data *data, int exitcode)
{
	int	i;

	i = 0;
	while (i < data->field_size.x)
	{
		free(data->field[i]);
		i++;
	}
	free(data->field);
	exit (exitcode);
}

int	i_winclose(void *param)
{
	free_and_quit((t_data *)param, 0);
	return (0);
}

int	i_keydown(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 53)
		free_and_quit(data, 0);
	return (0);
}
