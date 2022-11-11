/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawadh <hawadh@student.42Abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:42:22 by makhtar           #+#    #+#             */
/*   Updated: 2022/11/11 15:45:48 by hawadh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
**	Initialisation of the ray structure before the calculation
**/
static void	init_vars(t_ray *ray, t_info *inf, double *old_x, double *old_y)
{
	ray->x = inf->player->x_pos;
	ray->y = inf->player->y_pos;
	*old_x = ray->x;
	*old_y = ray->y;
	ray->wall = 0;
	ray->grid_x = (int)ray->x;
	ray->grid_y = (int)ray->y;
}

/**
**	The revised conditions if the angle is negative and the x_co exceeds 1920
**	calculating the adjacent side when wall hits
**/
static void	revise_calc(t_rays *rays, t_ray *ray, t_info *inf,
	int calc_height)
{
	if (calc_height == 0)
	{
		ray->angle += 0.000636318;
		ray->angle = fix_angle(ray->angle);
		if (ray->x1 > RAYS)
			ray->x1 = RAYS;
	}
	else
	{
		rays->dist = euclidean(ray,
				get_dist(inf->player->x_pos,
					inf->player->y_pos, ray->x, ray->y), inf->player->angle);
		rays->height
			= get_height(rays->dist,
				rays->ang, inf->player->angle);
	}
}

/**
**	Sub Main process which runs the rays for all the scenarios
**	Basic wall hits
**	Edge Cases
**	Direction of wall
**	Getting the height of the wall
**/
static void	hit_wall_check(t_ray *ray, t_info *inf)
{
	double		old_x;
	double		old_y;

	init_vars(ray, inf, &old_x, &old_y);
	while (!ray->wall)
	{
		old_x = ray->x;
		old_y = ray->y;
		raycasting(inf, ray);
	}
	inf->player->rays[RAYS - ray->count].dir_wall
		= wall_hit_direction(ray);
	inf->player->rays[RAYS - ray->count].x = ray->x;
	inf->player->rays[RAYS - ray->count].y = ray->y;
	inf->player->rays[RAYS - ray->count].side = ray->side;
	revise_calc(&inf->player->rays[RAYS - ray->count], ray, inf, 1);
}
/*
**	// printf("Angle of the player: %f, Height: %f, Angle of the ray: %f\n",
**	// 	(inf->player->angle * (180 / PI)), inf->player->rays[1920
**	// 	- ray->count].height, (inf->player->rays[1920 - ray->count].ang
* (180 / PI)));*/

/**
**	The Main Process of the raycasting which deals with pixel
**	put for ceiling, floor, walls
**/
void	init_rays(t_info *inf)
{
	t_ray	ray;

	ray.angle = inf->player->angle - (35 * RADIAN);
	ray.angle = fix_angle(ray.angle);
	ray.count = RAYS;
	ray.x1 = 0;
	ceiling_floor(inf);
	while (ray.count > 0)
	{
		hit_wall_check(&ray, inf);
		if (inf->player->door_collide == 1 && inf->player->door_flag == 1
			&& inf->integrate == 1)
			inf->integrate = 1;
		else
			inf->integrate = 0;
		ray.y = 540 - (inf->player->rays[RAYS - ray.count].height / 2);
		inf->player->rays[RAYS - ray.count].ang = ray.angle;
		revise_calc(NULL, &ray, inf, 0);
		place_walls(inf, inf->sprite, &inf->player->rays[RAYS - ray.count], ray.x1);
		ray.x1 += 1;
		ray.count--;
	}
	if (ray.spr != NULL)
		free_spr(ray.spr);
	init_cursor(inf);
}
