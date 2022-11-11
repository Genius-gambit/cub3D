/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawadh <hawadh@student.42Abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:28:29 by hawadh            #+#    #+#             */
/*   Updated: 2022/11/11 15:41:36 by hawadh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
**	Custom pixel put
**/
void	my_pixel_put(t_info *inf, int x, int y, int rgb)
{
	char	*draw;

	draw = inf->image->addr
		+ (y * inf->image->len + x * (inf->image->bitspix / 8));
	*(unsigned int *)draw = rgb;
}

/**
**	Function to calculate size of xpm and add them to image
**/
static void	add_xpm(t_info *info, t_xpm *xpm, t_rays *ray, int x)
{		
	int				xpm_y;
	int				xpm_x;
	int				y;
	int				i;

	xpm_y = 0;
	xpm_x = ray->y * xpm->wi;
	if (ray->side == 1)
		xpm_x = ray->x * xpm->wi;
	y = (HEIGHT - ray->height) / 2;
	while (y < HEIGHT)
	{
		i = 0;
		while (i < 4 && y >= 0 && xpm_y >= 0)
		{
			if (y >= 0 && xpm_y < ray->height)
				info->image->addr[((x * 4) + 4 * (WIDTH * y)) + i]
					= xpm->addr[((xpm_x * 4) + 4 * (xpm->wi * y)) + i];
			i++;
		}
		xpm_y++;
		y++;
	}
}

static void	add_sprite(t_info *inf, t_sprite *spr, t_rays *ray, int x)
{
	(void)inf;
	(void)spr;
	(void)ray;
	(void)x;
}

/*
*/
/**
**	Calls xpm struct based on player orientation
**/
void	place_walls(t_info *inf, t_sprite *spr, t_rays *ray, int x)
{
	static int	old_colour;

	if (!old_colour && ray->dir_wall != 5)
		old_colour = ray->dir_wall;
	if (ray->dir_wall == 1)
		add_xpm(inf, &inf->data->xpm[NO], ray, x);
	if (ray->dir_wall == 2)
		add_xpm(inf, &inf->data->xpm[SO], ray, x);
	if (ray->dir_wall == 3)
		add_xpm(inf, &inf->data->xpm[WE], ray, x);
	if (ray->dir_wall == 4)
		add_xpm(inf, &inf->data->xpm[EA], ray, x);
	if (ray->token == 5)
		add_xpm(inf, &inf->data->xpm[DO], ray, x);
	if (ray->token == 6)
		add_sprite(inf, spr, ray, x);
	else if (ray->dir_wall == 0 || ray->dir_wall == 5)
	{
		add_xpm(inf, &inf->data->xpm[old_colour - 1], ray, x);
		return ;
	}
	old_colour = ray->dir_wall;
}

/**
**	Draws everything include map
*	init_cursor(); to reinitialise crosshair
*	after each redraw
**/
void	draw_map(t_info *info)
{
	static int	timer;

	if (!timer)
	{
		find_player(info->data, info->player);
		timer = 1;
	}
	init_rays(info);
	draw_minimap(info, info->mini);
	init_cursor(info);
}
