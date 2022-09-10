/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:48:42 by lelhlami          #+#    #+#             */
/*   Updated: 2022/09/07 10:29:16 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_sprite(t_data *data, t_ray *ray, int angle)
{
    double h_spr;
	t_point p[2];
	int		row;
	double	pos_angle;

	pos_angle = get_pos_angle(angle);
	row = mapping(angle, get_range(data->player.angle - HFOV, \
		data->player.angle + HFOV), get_range(0, SCREENWIDTH));
    h_spr = SCREENHEIGHT * 10 / (ray->dis * cos(data->player.angle - angle));
	p[0].x = row;
	p[1].x = row;
	p[0].y = 0;
	p[1].y = (SCREENHEIGHT - h_spr) / 2;
	get_img_sprite(&data->map.spr, "./textures/ghost.xpm", data->mlx.mlx);
	draw_line_sprite(&data->mlx.img, &data->map.spr, p, row);
}

void	draw_line_sprite(t_img *img, t_sprite *spr, t_point *p, int row)
{
	t_point	middle;
	t_point	d;
	double	pixels;
	(void)p;
	(void)row;
	(void)spr;

	pixels = setup_draw_line(&p[0], &p[1], &middle, &d);
	d.x /= pixels;
	d.y /= pixels;
	while (middle.x < 0 && middle.y < 0 && pixels-- > 0)
	{
		middle.x += d.x;
		middle.y += d.y;
	}
	while (pixels-- > 0 && middle.x < SCREENWIDTH && middle.y < SCREENHEIGHT)
	{
		if (middle.x >= 0 && middle.x < SCREENWIDTH && \
			middle.y >= 0 && middle.y < SCREENHEIGHT)
			my_mlx_pixel_put(img, middle.x, middle.y, \
			get_color_from_img(&spr->img, \
mapping(row, get_range(0, GAP), get_range(0, spr->width)), \
mapping(middle.y, get_range(100, 150), get_range(0, spr->height))));
		middle.x += d.x;
		middle.y += d.y;
	}
}