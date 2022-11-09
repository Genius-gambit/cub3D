/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar <makhtar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:30:47 by makhtar           #+#    #+#             */
/*   Updated: 2022/11/08 14:34:33 by makhtar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	print_map(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

/**
**	Fetches the side of the wall when hitted with the ray
**/
int	wall_hit_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->cx < 0)
			return (3);
		else
			return (4);
	}
	else
	{
		if (ray->cy < 0)
			return (1);
		else
			return (2);
	}
	return (FALSE);
}
