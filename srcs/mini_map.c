/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar <makhtar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:43:20 by hawadh            #+#    #+#             */
/*   Updated: 2022/11/23 16:57:12 by makhtar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
**	Custom Pixel Put for Minimap
**/
void	mini_pixel_put(t_mini *mini, int x, int y, int rgb)
{
	char	*draw;

	draw = mini->addr + (y * mini->len + x * (mini->bitspix / 8));
	*(unsigned int *)draw = rgb;
}

/**
**	Draws Player at centre of minimap 
**/
static void	draw_mini_player(t_mini *mini, int x, int y, int rgb)
{
	int	x_reset;

	while (y < 100)
	{
		x_reset = x;
		while (x_reset < 100)
		{
			if (y == 80 || y == 99 || x_reset == 80 || x_reset == 99)
				mini_pixel_put(mini, x_reset, y, 0x000E5227);
			else
				mini_pixel_put(mini, x_reset, y, rgb);
			x_reset++;
		}
		y++;
	}
}

/**
**	Draws minimap interior
**/
void	draw_minimap(t_info *info, t_mini *mini)
{
	double	y;
	double	x;
	double	temp;
	int		i;
	int		j;

	modf(info->player->y_pos - 3.0, &temp);
	i = temp - 3;
	y = x_y_values(i, info->player->y_pos - 3.0) - extract_decimal(info->player->y_pos) * MINI_SCALE;
	i = assign_index(i);
	while (info->data->map[i] && mini_img_limit(y, x, 'y'))
	{
		modf(info->player->x_pos - 3.0, &temp);
		j = temp - 3;
		x = x_y_values(j, info->player->x_pos - 3.0) - extract_decimal(info->player->x_pos) * MINI_SCALE;
		j = assign_index(j);
		while (info->data->map[i][j] && mini_img_limit(y, x, 'x'))
		{
			mini_pixel_put(mini, x, y, rgb(info->data, 1));
			x++;
		}
		y++;
	}
	mini_interior(info, mini);
	draw_mini_player(mini, 80, 80, 0x003D8758);
}

/**
**	Draws closer borders and calls function to draw
**	Outer borders. Calls to draw minimap interior
**/
void	draw_minimap(t_info *info, t_mini *mini)
{
	int	x;
	int	y;

	y = 3;
	while (y < MINI_DIM - 3)
	{
		x = 3;
		while (x < MINI_DIM - 3)
		{
			mini_pixel_put(mini, x, y, 0X00000048);
			x++;
		}
		y++;
	}
	mini_interior(info);
	// mini_rot(info);
	draw_mini_player(mini, (MINI_DIM / 2) - 4, (MINI_DIM / 2) - 4, 0x003D8758);
}

/**
**	Initialises struct mini and creates new image for
**	mini-map
**/
void	init_minimap(t_info *info)
{
	t_mini	*mini;

	mini = (t_mini *)ft_calloc(1, sizeof(t_mini));
	info->mini = mini;
	info->mini_map = mlx_new_image(info->mlx, MINI_DIM, MINI_DIM);
	if (!info->mini_map)
	{
		free_data(info);
		err_return(4, info);
	}
	mini->addr = mlx_get_data_addr(info->mini_map, &mini->bitspix,
			&mini->len, &mini->end);
	if (!mini->addr)
		err_return(4, info);
}
