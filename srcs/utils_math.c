/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar <makhtar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:44:02 by makhtar           #+#    #+#             */
/*   Updated: 2022/11/16 15:57:47 by makhtar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
**	Extracts Decimal point.
**/
double	extract_decimal(t_player *player, char status)
{
	double			diff;
	static double	old_y;
	static double	old_x;

	if (status == 'y')
	{
		diff = modf(player->y_pos, &diff);
		if (old_y < player->y_pos)
			diff *= -1;
		old_y = player->y_pos;
	}
	if (status == 'x')
	{
		diff = modf(player->x_pos, &diff);
		if (old_x < player->x_pos)
			diff *= -1;
		old_x = player->x_pos;
	}
	return (diff);
}

double	sq(double num)
{
	return (num * num);
}

double	get_dist(double x_one, double y_one, double x_two, double y_two)
{
	double	dist;

	dist = sqrt(sq(x_two - x_one) + sq(y_two - y_one));
	return (dist);
}

double	euclidean(t_ray *ray, double dist, double p_ang)
{
	double		real_dist;
	static int	rays;

	real_dist = 0;
	real_dist = cos(ray->angle - p_ang) * dist;
	if (real_dist < 0)
		real_dist *= -1;
	rays++;
	if (rays == RAYS)
		rays = 0;
	return (real_dist);
}

/**
**	Calculates the height of wall for each ray.
**/
double	get_height(double dist)
{
	double	height;

	height = (BLOCK_SIZE * 62.5) / dist;
	return (height);
}
