/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawadh <hawadh@student.42Abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:47:50 by hawadh            #+#    #+#             */
/*   Updated: 2022/11/24 21:06:25 by hawadh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_config_lines(char *input)
{
	static char	xpm[5][3] = {"NO", "SO", "WE", "EA", ""};
	static char	colours[3][2] = {"C", "F", ""};
	int			i;

	i = 0;
	while (xpm[i][0])
	{
		if (input && !ft_strncmp(input, xpm[i], 2))
			return (1);
		i++;
	}
	i = 0;
	while (colours[i][0])
	{
		if (input && !ft_strncmp(input, colours[i], 1))
			return (1);
		i++;
	}
	return (0);
}
