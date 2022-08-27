/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:35:39 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 11:36:20 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *img, t_point *begin, t_point *end, \
		int color)
{
	t_point	middle;
	t_point	d;
	double	pixels;

	pixels = setup_draw_line(begin, end, &middle, &d);
	d.x /= pixels;
	d.y /= pixels;
	while (pixels-- > 0)
	{
		my_mlx_pixel_put(img, middle.x, middle.y, color);
		middle.x += d.x;
		middle.y += d.y;
	}
}

void	draw_line_texture(t_img *img, t_txr *txr, t_point *p, int row)
{
	t_point	middle;
	t_point	d;
	double	pixels;

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
			get_color_from_img(&txr->img, \
mapping(row, get_range(0, GAP), get_range(0, txr->width)), \
mapping(middle.y, get_range(p[0].y, p[1].y), get_range(0, txr->height))));
		middle.x += d.x;
		middle.y += d.y;
	}
}

double	setup_draw_line(t_point *begin, t_point *end, \
						t_point *middle, t_point *d)
{
	middle->x = begin->x;
	middle->y = begin->y;
	d->x = end->x - begin->x;
	d->y = end->y - begin->y;
	return (sqrt((d->x * d->x) + (d->y * d->y)));
}

int	get_rgb(t_rgb color)
{
	return (((int)color.r << 16) + ((int)color.g << 8) + ((int)color.b));
}
