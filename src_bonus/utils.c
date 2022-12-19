/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:51:25 by fgeslin           #+#    #+#             */
/*   Updated: 2022/12/19 12:47:14 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/fdf.h"

void	set_int2(t_int2 *int2, int a, int b)
{
	int2->x = a;
	int2->y = b;
}

void	set_float2(t_float2 *float2, float a, float b)
{
	float2->x = a;
	float2->y = b;
}
