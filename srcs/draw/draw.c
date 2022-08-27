/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:08:35 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 11:14:56 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	draw_rays(data);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
							data->mlx.img.img, 0, 0);
}

double	get_pos_angle(double angle)
{
	if (angle < 0)
		return (2 * PI + angle);
	else if (angle > 2 * PI)
		return (angle - 2 * PI);
	return (angle);
}
