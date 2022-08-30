/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:23:58 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 16:39:00 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_data *data)
{
	t_ray	ray_x;
	t_ray	ray_y;
	double	r_angle;
	double	pos_r_angle;

	r_angle = data->player.angle - HFOV;
	while (r_angle <= data->player.angle + HFOV)
	{
		pos_r_angle = get_pos_angle(r_angle);
		raycast_x(&ray_x, &data->map, &data->player, pos_r_angle);
		raycast_y(&ray_y, &data->map, &data->player, pos_r_angle);
		if (ray_x.dis >= ray_y.dis)
			draw_ray_y(&ray_y, data, r_angle);
		else
			draw_ray_x(&ray_x, data, r_angle);
		r_angle += PI / 6000;
	}
}

int	is_pn_in_blk(t_block *block, t_point *point)
{
	if (point->x >= block->top_left.x && \
		point->y >= block->top_left.y && \
		point->x <= block->bottom_right.x && \
		point->y <= block->bottom_right.y)
		return (1);
	return (0);
}

double	distance(t_point *p1, t_point *p2)
{
	return (sqrt((p1->x - p2->x) * (p1->x - p2->x) + \
				(p1->y - p2->y) * (p1->y - p2->y)));
}

t_point	get_range(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

double	mapping(double p, t_point in, t_point out)
{
	return ((p - in.x) * (out.y - out.x) / (in.y - in.x) + out.x);
}
