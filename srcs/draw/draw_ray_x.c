/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 08:51:28 by zwina             #+#    #+#             */
/*   Updated: 2022/08/13 17:33:54 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_x(t_ray *ray, t_data *data, double angle)
{
	t_point	p[2];
	int		row;
	double	h;
	double	pos_angle;

	pos_angle = get_pos_angle(angle);
	row = mapping(angle, get_range(data->player.angle - HFOV, \
		data->player.angle + HFOV), get_range(0, SCREENWIDTH));
	h = SCREENHEIGHT * 100 / (ray->dis * cos(data->player.angle - angle));
	p[0].x = row;
	p[1].x = row;
	p[0].y = 0;
	p[1].y = (SCREENHEIGHT - h) / 2;
	draw_line(&data->mlx.img, &p[0], &p[1], get_rgb(data->map.ceiling));
	p[0].y = p[1].y;
	p[1].y += h;
	if (pos_angle > PI / 2 && pos_angle < (3 * PI) / 2)
		draw_line_texture(&data->mlx.img, &data->map.ea, p, \
			(int)ray->rp.y % GAP);
	else
		draw_line_texture(&data->mlx.img, &data->map.we, p, \
			(int)ray->rp.y % GAP);
	p[0].y = p[1].y;
	p[1].y = SCREENHEIGHT;
	draw_line(&data->mlx.img, &p[0], &p[1], get_rgb(data->map.floor));
}
