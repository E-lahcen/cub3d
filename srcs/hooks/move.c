/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:58:51 by zwina             #+#    #+#             */
/*   Updated: 2022/08/08 16:40:36 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(int key_code, t_data *data)
{
	t_point	translater;

	set_translater(key_code, &data->player, &translater);
	if (data->map.grid[(int)(data->player.pos.y + translater.y) / \
		GAP][data->player.x].c == '0')
		data->player.pos.y += translater.y;
	if (data->map.grid[data->player.y][(int)(data->player.pos.x + \
		translater.x) / GAP].c == '0')
		data->player.pos.x += translater.x;
	player_in_grid(&data->map, &data->player);
	re_draw(data);
}

void	set_translater(int key_code, t_player *player, t_point *translater)
{
	if (key_code == UP)
	{
		translater->y = player->dir.y * 5;
		translater->x = player->dir.x * 5;
	}
	else if (key_code == RIGHT)
	{
		translater->y = player->sid.y * 5;
		translater->x = player->sid.x * 5;
	}
	else if (key_code == DOWN)
	{
		translater->y = -player->dir.y * 5;
		translater->x = -player->dir.x * 5;
	}
	else if (key_code == LEFT)
	{
		translater->y = -player->sid.y * 5;
		translater->x = -player->sid.x * 5;
	}
}

void	player_in_grid(t_map *map, t_player *player)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (player->pos.y >= map->grid[i][j].top_left.y && \
				player->pos.x >= map->grid[i][j].top_left.x && \
				player->pos.y <= map->grid[i][j].bottom_right.y && \
				player->pos.x <= map->grid[i][j].bottom_right.x)
			{
				player->y = i;
				player->x = j;
				return ;
			}
		}
	}
}
