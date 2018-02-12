/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:22:28 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 14:47:34 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				draw_point(t_point *new, t_env *env,
		t_point *p, int original_z)
{
	int				pos;
	unsigned int	hex;

	if (p->color == 0)
		hex = get_red_shade(env, new, original_z);
	else
		hex = p->color;
	pos = nearbyint(nearbyint(new->y) * env->win_width + nearbyint(new->x));
	if (new->x >= 0 && new->x < 2560 && new->y < 1440 && new->y >= 0
			&& pos >= 0 && pos < env->win_width * env->win_height)
	{
		if (env->data_addr[pos] < mlx_get_color_value(env->mlx, hex))
			env->data_addr[pos] = mlx_get_color_value(env->mlx, hex);
	}
}

void				draw_on_x_axis(double difx,
		t_point *p1, t_point *p2, t_env *env)
{
	t_point		tmp;
	double		newx;

	while (difx)
	{
		tmp.original_z = get_new_z(p1, p2, difx);
		newx = (p1->x > p2->x) ? p1->x - difx : p1->x + difx;
		tmp.z = get_new_real_z(p1, p2, difx);
		tmp.x = newx;
		tmp.y = p1->y;
		draw_point(&tmp, env, p1, tmp.original_z);
		difx--;
	}
}

int					draw_line_between_points(t_point *p1,
		t_point *p2, t_env *env)
{
	double		difx;
	double		dify;
	double		newx;
	t_point		tmp;

	difx = fabs(p1->x - p2->x);
	dify = fabs(p1->y - p2->y);
	if (dify == 0)
		draw_on_x_axis(difx, p1, p2, env);
	else if (difx == 0)
	{
		while (dify)
		{
			tmp.original_z = get_new_z(p1, p2, dify);
			newx = (p1->y > p2->y) ? p1->y - dify : p1->y + dify;
			tmp.z = get_new_real_z(p1, p2, dify);
			tmp.x = p1->x;
			tmp.y = newx;
			draw_point(&tmp, env, p1, tmp.original_z);
			dify--;
		}
	}
	else
		get_diagonal_point(p1, p2, env);
	return (1);
}

int					points_to_image(t_line *matrix, t_env *env)
{
	int			y;
	int			x;
	t_point		***points;

	points = matrix->points;
	matrix->total_real = fabs(matrix->max_real_z) + fabs(matrix->min_real_z);
	y = 0;
	while (y < matrix->height)
	{
		x = 0;
		while (x < matrix->width)
		{
			draw_point(points[y][x], env, points[y][x],
					points[y][x]->original_z);
			if (x < matrix->width - 1)
				draw_line_between_points(points[y][x], points[y][x + 1], env);
			if (y < matrix->height - 1)
				draw_line_between_points(points[y][x], points[y + 1][x], env);
			x++;
		}
		y++;
	}
	return (1);
}

int					fdf_handler(t_line *matrix, t_env *env)
{
	points_to_image(matrix, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	events_listener(env);
	mlx_loop(env->mlx);
	return (1);
}
