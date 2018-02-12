/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:46:51 by cvermand          #+#    #+#             */
/*   Updated: 2018/02/12 14:11:16 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int			rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;

	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

unsigned int			hsl_to_rgb(double ch, double min, int hue)
{
	double			(*r)(double);
	unsigned int	(*rgb)(int, int, int);
	double			x;

	x = ch * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	r = &round;
	rgb = &rgb_to_hex;
	if (hue >= 0 && hue <= 60)
		return (rgb(r((ch + min) * 255), r((x + min) * 255), r(min * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb(r((x + min) * 255), r((ch + min) * 255), r(min * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb(r((min) * 255), r((ch + min) * 255), r((x + min) * 255)));
	if (hue > 180 && hue <= 240)
		return (rgb(r(min * 255), r((x + min) * 255), r((ch + min) * 255)));
	else
		return (rgb(r((x + min) * 255), r((min) * 255), r((ch + min) * 255)));
	return (0);
}

unsigned int			hsv_calculator(t_point *new, t_line *matrix,
		int original_z, t_env *env)
{
	int		hue;
	double	saturation;
	double	bright;
	double	chroma;
	double	min;

	saturation = (!env->color) ? 0 : 0.79;
	if (original_z >= 0 && matrix->max_z != 0 && env->color)
		hue = (int)round(90.0 - ((((double)original_z /
							(double)matrix->max_z)) * 90.0));
	else if (original_z < 0 && matrix->min_z != 0 && env->color)
		hue = fmin((int)round(140.0 + (fabs(((double)original_z /
								(double)matrix->min_z)) * 140.0)), 255.0);
	else
		hue = 90;
	if (env->bright)
		bright = fmax((fabs(new->z + fabs(matrix->min_real_z))
					/ matrix->total_real), 0.25);
	else
		bright = 0.70;
	chroma = bright * saturation;
	min = bright - chroma;
	return (hsl_to_rgb(chroma, min, hue));
}

unsigned int			get_red_shade(t_env *env, t_point *new, int original_z)
{
	int		max_z;
	int		min_z;
	int		new_z;

	max_z = (env->matrix)->max_z;
	new_z = max_z - original_z;
	min_z = (env->matrix)->min_z;
	return (hsv_calculator(new, env->matrix, original_z, env));
}
