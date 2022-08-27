/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:03:08 by lelhlami          #+#    #+#             */
/*   Updated: 2022/08/27 12:33:13 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_data *data)
{
	int		i;

	i = -1;
	data->map.mini_map = (char **)malloc(sizeof(char *) * 10);
	if (!data->map.mini_map)
		errors("Error in allocation with malloc", NULL);
	while (++i < 10)
		data->map.mini_map[i] = (char *)malloc(sizeof(char) * 20);
	set_mini_map(data);
	draw_mini_map_player(data);
	free_double(data->map.mini_map);
}

void	draw_mini_map_player(t_data *data)
{
	size_t  x;
	size_t  y;

	x = 100;
	y = 800;
	while (y < SCREENHEIGHT - 50)
	{
		x = 100;
		while (x < 400)
		{
			if (x <= 100 + MINIMAPWIDTH / 2 + 5 \
				&& x >= 100 + MINIMAPWIDTH / 2 - 5 \
				&& y <= 800 + MINIMAPHEIGHT / 2 + 5 \
				&& y >= 800 + MINIMAPHEIGHT / 2 - 5)
				my_mlx_pixel_put(&data->mlx.img, x, y, 1111111);
			else
			{
				
				my_mlx_pixel_put(&data->mlx.img, x, y, 0000000);
			}
			x++;
		}
		y++;
	}
}

void    set_mini_map(t_data *data)
{
	int     limit_top_y;
	int     limit_bottom_y;
	int     limit_right_x;
	int     limit_left_x;
	int     cnt_i;
	int     cnt_j;

	cnt_i = 0;
	cnt_j = 0;
	limit_left_x = data->player.x - 10;
	limit_top_y = data->player.y - 5;
	limit_right_x = data->player.x + 10;
	limit_bottom_y = data->player.y + 5;
	while (cnt_i < 10)
	{
		cnt_j = 0;
		while (cnt_j < 20)
		{
			if (limit_left_x < 0 || limit_top_y < 0 \
				|| limit_right_x > (int)data->map.width \
				|| limit_bottom_y > (int)data->map.height \
				|| (data->map.map[limit_top_y][limit_left_x] != '0' \
				&& !is_player(data->map.map[limit_top_y][limit_left_x])))
					data->map.mini_map[cnt_i][cnt_j] = '1';
			else if (data->map.map[limit_top_y][limit_left_x] == '0' \
					|| is_player(data->map.map[limit_top_y][limit_left_x]))
				data->map.mini_map[cnt_i][cnt_j] = data->map.map[limit_top_y][limit_left_x];
			cnt_j++;
			limit_left_x++;
		}
		cnt_i++;
		limit_top_y++;
	}
	print_maps(data);
}

void	print_maps(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 20)
			printf("%c ", data->map.mini_map[i][j]);
		printf("\n");
	}
}

void	free_double(char **tab)
{
	size_t	i;

	i = 0;
	while (i < 10)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
