/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:56:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 18:34:25 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_diagonal_point(t_point *p1, t_point *p2, t_env *env)
{
	double		difx;
	double		dify;
	double		tan;

	difx = fabs(p1->x - p2->x);
	dify = fabs(p1->y - p2->y);
	tan = dify / difx;
	if (p1->x < p2->x && p1->y < p2->y)
		north_east_line(p1, p2, env, tan);
	if (p1->x < p2->x && p1->y > p2->y)
		north_west_line(p1, p2, env, tan);
	if (p1->x > p2->x && p1->y < p2->y)
		south_east_line(p1, p2, env, tan);
	if (p1->x > p2->x && p1->y > p2->y)
		south_west_line(p1, p2, env, tan);
	return (1);
}

void	north_east_line(t_point *p1, t_point *p2, t_env *env, double tan)
{
	int			prev_y;
	double		new_y;
	int			x;
	t_point		tmp;
	int			sign;

	x = 1;
	prev_y = (int)p1->y;
	while (x + p1->x <= p2->x)
	{
		sign = get_new_z(p1, p2, x);
		tmp.z = get_new_real_z(p1, p2, x);
		new_y = p1->y + (tan * (double)(x));
		while (nearbyint(++prev_y) < nearbyint(new_y))
		{
			tmp.x = x + p1->x;
			tmp.y = prev_y;
			draw_point(&tmp, env, p1, sign);
		}
		tmp.x = x + p1->x;
		tmp.y = prev_y;
		draw_point(&tmp, env, p1, sign);
		prev_y = new_y;
		x++;
	}
}

void	north_west_line(t_point *p1, t_point *p2, t_env *env, double tan)
{
	int			prev_y;
	double		new_y;
	int			x;
	t_point		tmp;
	int			sign;

	x = 1;
	prev_y = p1->y;
	while (x + p1->x <= p2->x)
	{
		new_y = (p1->y - (tan * (double)(x)));
		sign = get_new_z(p1, p2, x);
		tmp.z = get_new_real_z(p1, p2, x);
		while (--prev_y > new_y)
		{
			tmp.x = x + p1->x;
			tmp.y = prev_y;
			draw_point(&tmp, env, p1, sign);
		}
		tmp.x = x + p1->x;
		tmp.y = prev_y;
		draw_point(&tmp, env, p1, sign);
		prev_y = new_y;
		x++;
	}
}

void	south_east_line(t_point *p1, t_point *p2, t_env *env, double tan)
{
	int			prev_y;
	double		new_y;
	int			x;
	t_point		tmp;
	int			sign;

	x = 1;
	prev_y = p1->y;
	while (p1->x - x >= p2->x)
	{
		new_y = (p1->y + (tan * (double)(x)));
		sign = get_new_z(p1, p2, x);
		tmp.z = get_new_real_z(p1, p2, x);
		while (++prev_y < new_y)
		{
			tmp.x = p1->x - x;
			tmp.y = prev_y;
			draw_point(&tmp, env, p1, sign);
		}
		tmp.x = p1->x - x;
		tmp.y = prev_y;
		draw_point(&tmp, env, p1, sign);
		prev_y = new_y;
		x++;
	}
}

void	south_west_line(t_point *p1, t_point *p2, t_env *env, double tan)
{
	int			prev_y;
	double		new_y;
	int			x;
	t_point		tmp;
	int			sign;

	x = 1;
	prev_y = p1->y;
	while (p1->x - x >= p2->x)
	{
		sign = get_new_z(p1, p2, x);
		tmp.z = get_new_real_z(p1, p2, x);
		new_y = (p1->y - (tan * (double)(x)));
		while (--prev_y > new_y)
		{
			tmp.x = p1->x - x;
			tmp.y = prev_y;
			draw_point(&tmp, env, p1, sign);
		}
		tmp.x = p1->x - x;
		tmp.y = prev_y;
		draw_point(&tmp, env, p1, sign);
		prev_y = new_y;
		x++;
	}
}
