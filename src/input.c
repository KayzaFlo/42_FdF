/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:30:30 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/13 13:51:55 by fgeslin          ###   ########.fr       */
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
	if (key == 53)
		free_and_quit((t_data *)param, 0);
	return (0);
}
