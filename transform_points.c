/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:40:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 18:35:59 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				init_scale(double scale, t_transform *t, t_line *matrix)
{
	(void)matrix;
	t->x[0] = scale;
	t->x[1] = 0;
	t->x[2] = 0;
	t->x[3] = 0;
	t->y[0] = 0;
	t->y[1] = scale;
	t->y[2] = 0;
	t->y[3] = 0;
	t->z[0] = 0;
	t->z[1] = 0;
	t->z[2] = scale;
	t->z[3] = 1;
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = 0;
	t->w[3] = 1;
}

void				init_trans(int x_center, int y_center, t_transform *t)
{
	t->x[0] = 1;
	t->x[1] = 0;
	t->x[2] = 0;
	t->x[3] = x_center;
	t->y[0] = 0;
	t->y[1] = 1;
	t->y[2] = 0;
	t->y[3] = y_center;
	t->z[0] = 0;
	t->z[1] = 0;
	t->z[2] = 1;
	t->z[3] = 0;
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = 0;
	t->w[3] = 1;
}

void				matrix_multiplication(t_transform *t, t_point *point)
{
	double			x;
	double			y;
	double			z;
	double			w;

	x = (double)(point->x * t->x[0] + point->y * t->x[1]
			+ point->z * t->x[2] + point->w * t->x[3]);
	y = (double)(point->x * t->y[0] + point->y * t->y[1]
			+ point->z * t->y[2] + point->w * t->y[3]);
	z = (double)(point->x * t->z[0] + point->y * t->z[1]
			+ point->z * t->z[2] + point->w * t->z[3]);
	w = (double)(point->x * t->w[0] + point->y * t->w[1]
			+ point->z * t->w[2] + point->w * t->w[3]);
	point->x = x;
	point->y = y;
	point->z = z;
	point->w = w;
}

void				transform_points_bis(t_line *matrix, t_transform scale)
{
	int				y;
	int				x;
	t_point			***points;

	points = matrix->points;
	matrix->min_real_z = points[0][0]->z;
	y = 0;
	while (y < matrix->height)
	{
		x = 0;
		while (x < matrix->width)
		{
			initialise_points(points[y][x]);
			matrix_multiplication(&scale, points[y][x]);
			matrix_multiplication_plus(matrix, points[y][x], 'x');
			matrix_multiplication_plus(matrix, points[y][x], 'y');
			matrix_multiplication_plus(matrix, points[y][x], 'z');
			if (points[y][x]->z > matrix->max_real_z)
				matrix->max_real_z = points[y][x]->z;
			if (points[y][x]->z < matrix->min_real_z)
				matrix->min_real_z = points[y][x]->z;
			x++;
		}
		y++;
	}
}

void				transform_points(t_line *matrix)
{
	t_point			***points;
	t_transform		scale;
	t_transform		translation;

	points = matrix->points;
	init_scale(matrix->scale, &scale, matrix);
	transform_points_bis(matrix, scale);
	init_trans(
			matrix->margin_x - (int)points[matrix->height / 2]
			[matrix->width / 2]->x,
			matrix->margin_y - (int)points[matrix->height / 2]
			[matrix->width / 2]->y, &translation);
	matrix_multiplication_bis(matrix, &translation, &points);
}
