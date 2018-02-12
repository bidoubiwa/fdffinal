/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:19:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 14:28:42 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_new_real_z(t_point *p1, t_point *p2, int x)
{
	double		difx;
	double		difz;
	double		dify;

	difz = fabs(p1->z - p2->z);
	difx = fabs(p1->x - p2->x);
	dify = fabs(p1->y - p2->y);
	if (p1->z == p2->z)
		return (p1->z);
	else if (p1->z < p2->z && difx != 0)
		return ((int)fmin(p1->z, p2->z) +
				(int)(ceil(difz * (double)x / difx)));
	else if (p1->z < p2->z && dify != 0)
		return ((int)fmin(p1->z, p2->z) +
				(int)(ceil(difz * (double)x / dify)));
	else if (p1->z > p2->z && difx != 0)
		return ((int)fmin(p1->z, p2->z) +
				(int)(difz + 1) - (int)(ceil(difz * (double)x / difx)));
	else if (p1->z > p2->z && dify != 0)
	{
		return ((int)fmin(p1->z, p2->z) +
				(int)(difz + 1) - (int)(ceil(difz * (double)x / dify)));
	}
	return (0);
}

int			get_new_z(t_point *p1, t_point *p2, int x)
{
	double		difx;
	double		difz;
	double		dify;

	difz = fabs(p1->original_z - p2->original_z);
	difx = fabs(p1->x - p2->x);
	dify = fabs(p1->y - p2->y);
	if (p1->original_z == p2->original_z)
		return (p1->original_z);
	else if (p1->original_z < p2->original_z && difx != 0)
		return ((int)fmin(p1->original_z, p2->original_z) +
				(int)(ceil(difz * (double)x / difx)));
	else if (p1->original_z < p2->original_z && dify != 0)
		return ((int)fmin(p1->original_z, p2->original_z) +
				(int)(ceil(difz * (double)x / dify)));
	else if (p1->original_z > p2->original_z && difx != 0)
		return ((int)fmin(p1->original_z, p2->original_z) +
				(int)(difz + 1) - (int)(ceil(difz * (double)x / difx)));
	else if (p1->original_z > p2->original_z && dify != 0)
	{
		return ((int)fmin(p1->original_z, p2->original_z) +
				(int)(difz + 1) - (int)(ceil(difz * (double)x / dify)));
	}
	return (0);
}
