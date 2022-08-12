/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:08:35 by zwina             #+#    #+#             */
/*   Updated: 2022/08/08 11:51:07 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			draw_block(&data->mlx.img, &data->map.grid[i][j]);
			j++;
		}
		i++;
	}
	draw_player(&data->mlx.img, &data->player);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
							data->mlx.img.img, 0, 0);
}

void	draw_block(t_img *img, t_block *square)
{
	if (square->c == '1')
		draw_square_fill(img, &square->top_left, &square->bottom_right, \
			0x707070);
	else if (square->c == '0' || \
			square->c == 'N' || \
			square->c == 'E' || \
			square->c == 'S' || \
			square->c == 'W')
		draw_square_fill(img, &square->top_left, &square->bottom_right, \
			0xf0f0f0);
}

void	draw_square_fill(t_img *img, t_point *top_left, \
						t_point *bottom_right, int color)
{
	int	x;
	int	y;

	y = top_left->y;
	while (y <= bottom_right->y)
	{
		x = top_left->x;
		while (x <= bottom_right->x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_square_empty(t_img *img, t_point *top_left, \
						t_point *bottom_right, int color)
{
	int	i;
	int	j;
	int	k;

	i = top_left->y;
	j = bottom_right->y;
	k = top_left->x;
	while (k <= bottom_right->x)
	{
		my_mlx_pixel_put(img, k, i, color);
		my_mlx_pixel_put(img, k, j, color);
		k++;
	}
	i = top_left->x;
	j = bottom_right->x;
	k = top_left->y;
	while (k <= bottom_right->y)
	{
		my_mlx_pixel_put(img, i, k, color);
		my_mlx_pixel_put(img, j, k, color);
		k++;
	}
}

void	draw_player(t_img *img, t_player *player)
{
	t_block	player_block;
	t_point	dir;
	t_point	sid;

	player_block.top_left.y = player->pos.y - 5;
	player_block.top_left.x = player->pos.x - 5;
	player_block.bottom_right.y = player->pos.y + 5;
	player_block.bottom_right.x = player->pos.x + 5;
	draw_square_fill(img, &player_block.top_left, &player_block.bottom_right, \
						0xf00000);
	dir.y = player->pos.y + player->dir.y * 20;
	dir.x = player->pos.x + player->dir.x * 20;
	sid.y = player->pos.y + player->sid.y * 10;
	sid.x = player->pos.x + player->sid.x * 10;
	draw_line(img, &player->pos, &dir, 0x00ff00);
	draw_line(img, &player->pos, &sid, 0x0000ff);
}
