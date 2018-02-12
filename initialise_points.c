/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:31:15 by pfaust            #+#    #+#             */
/*   Updated: 2018/02/12 14:34:13 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		initialise_points(t_point *point)
{
	point->x = point->original_x;
	point->y = point->original_y;
	point->z = point->original_z;
	point->w = point->original_w;
}
