/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points_extra.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:15:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 18:36:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			x_multiplication(t_line *matrix,
		int *y, int *z, t_point *point)
{
	*y = (int)(point->y * cos(matrix->rotation_x)
			- point->z * sin(matrix->rotation_x));
	*z = (int)(point->y * sin(matrix->rotation_x)
			+ point->z * cos(matrix->rotation_x));
}

static void			y_multiplication(t_line *matrix,
		int *x, int *z, t_point *point)
{
	*x = point->x * cos(matrix->rotation_y)
		+ point->z * sin(matrix->rotation_y);
	*z = (1 - point->x * sin(matrix->rotation_y))
		+ point->z * cos(matrix->rotation_y);
}

static void			z_multiplication(t_line *matrix,
		int *x, int *y, t_point *point)
{
	*x = point->x * cos(matrix->rotation_z)
		- point->y * sin(matrix->rotation_z);
	*y = point->x * sin(matrix->rotation_z)
		+ point->y * cos(matrix->rotation_z);
}

void				matrix_multiplication_plus(t_line *matrix,
		t_point *point, char c)
{
	int x;
	int y;
	int z;

	x = 0;
	y = 0;
	z = 0;
	if (c == 'x')
	{
		x = 1 * point->x;
		x_multiplication(matrix, &y, &z, point);
	}
	else if (c == 'y')
	{
		y = point->y;
		y_multiplication(matrix, &x, &z, point);
	}
	else
	{
		z = point->z;
		z_multiplication(matrix, &x, &y, point);
	}
	point->x = x;
	point->y = y;
	point->z = z;
}

void				matrix_multiplication_bis(t_line *matrix,
		t_transform *translation, t_point ****points)
{
	int		y;
	int		x;

	y = 0;
	while (y < matrix->height)
	{
		x = 0;
		while (x < matrix->width)
		{
			matrix_multiplication(translation, (*points)[y][x]);
			x++;
		}
		y++;
	}
}
