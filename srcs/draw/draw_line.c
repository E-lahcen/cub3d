/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:35:39 by zwina             #+#    #+#             */
/*   Updated: 2022/08/07 16:57:56 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *img, const t_point *begin, const t_point *end, \
		int color)
{
	t_point	middle;
	double	dx;
	double	dy;
	double	pixels;

	middle.x = begin->x;
	middle.y = begin->y;
	dx = end->x - begin->x;
	dy = end->y - begin->y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	while (pixels-- > 0)
	{
		my_mlx_pixel_put(img, middle.x, middle.y, color);
		middle.x += dx;
		middle.y += dy;
	}
}

void	draw_line_stroke(t_img *img, const t_block *begin, \
									const t_block *end, int color)
{
	t_block	middle;
	double	dx;
	double	dy;
	double	pixels;

	middle.top_left.y = begin->top_left.y;
	middle.top_left.x = begin->top_left.x;
	middle.bottom_right.y = begin->bottom_right.y;
	middle.bottom_right.x = begin->bottom_right.x;
	dx = end->top_left.x - begin->top_left.x;
	dy = end->top_left.y - begin->top_left.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	while (pixels-- > 0)
	{
		draw_square_fill(img, &middle.top_left, &middle.bottom_right, color);
		middle.top_left.x += dx;
		middle.top_left.y += dy;
		middle.bottom_right.x += dx;
		middle.bottom_right.y += dy;
	}
}
