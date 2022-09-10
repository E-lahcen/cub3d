/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:36:12 by lelhlami          #+#    #+#             */
/*   Updated: 2022/09/06 11:42:48 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    set_mini_map(t_data *data)
{
	int     limit_top_y;
	int     limit_left_x;
	int     cnt_i;
	int     cnt_j;

	cnt_i = -1;
	limit_left_x = data->player.x - 7;
	limit_top_y = data->player.y - 7;
	// print_map(&data->map);
	while (++cnt_i < 15)
	{
		cnt_j = -1;
		limit_left_x = data->player.x - 7;
		while (++cnt_j < 15)
		{
			if (cnt_j == 7 && cnt_i == 7)
				data->map.mini_map[cnt_i][cnt_j] = 'N';
			else if (limit_left_x < 0 || limit_top_y < 0 || \
				limit_left_x >= (int)data->map.width || \
				limit_top_y >= (int)data->map.height || \
				data->map.map[limit_top_y][limit_left_x] == '\0')
				data->map.mini_map[cnt_i][cnt_j] = '2';
			else if (data->map.map[limit_top_y][limit_left_x] == '0' || \
					is_player(data->map.map[limit_top_y][limit_left_x]))
				data->map.mini_map[cnt_i][cnt_j] = '0';
			else if (data->map.map[limit_top_y][limit_left_x] == '1')
				data->map.mini_map[cnt_i][cnt_j] = '1';
			else if (data->map.map[limit_top_y][limit_left_x] == '3')
				data->map.mini_map[cnt_i][cnt_j] = '3';
			limit_left_x++;
		}
		limit_top_y++;
	}
	print_maps(data);
}

void	print_maps(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 15)
	{
		j = -1;
		while (++j < 15)
			printf("%c ", data->map.mini_map[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

void	free_double(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < 15)
	{
		free(data->map.mini_map[i]);
		free(data->map.mini_grid[i]);
		i++;
	}
	free(data->map.mini_map);
	free(data->map.mini_grid);
}

void	mini_setup_grid(t_data *data)
{
	size_t	i;
	size_t	j;

	data->map.mini_grid = (t_block **)malloc(sizeof(t_block *) * 15);
	i = -1;
	while (++i < 15)
		data->map.mini_grid[i] = (t_block *)malloc(sizeof(t_block) * 15);
	i = -1;
	while (++i < 15)
	{
		j = -1;
		while (++j < 15)
		{
			data->map.mini_grid[i][j].top_left.y = i * MINIGAP;
			data->map.mini_grid[i][j].top_left.x = j * MINIGAP;
			data->map.mini_grid[i][j].bottom_right.y = i * MINIGAP + MINIGAP;
			data->map.mini_grid[i][j].bottom_right.x = j * MINIGAP + MINIGAP;
			data->map.mini_grid[i][j].c = data->map.mini_map[i][j];
		}
	}
}