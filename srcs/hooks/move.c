/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:58:51 by zwina             #+#    #+#             */
/*   Updated: 2022/08/26 23:17:25 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(int key_code, t_data *data)
{
	t_point	to_go[3];

	set_translater(key_code, &data->player, to_go);
	to_go[0].y = to_go[1].y;
	to_go[0].x = to_go[2].x;
	if (can_he_move_to(&to_go[0], &data->map, &data->player))
		moving(&data->player, &to_go[0]);
	else
	{
		if (can_he_move_to(&to_go[1], &data->map, &data->player) && \
			can_he_move_to(&to_go[2], &data->map, &data->player))
		{
			if ((int)fabs(data->player.pos.y - to_go[1].y) >= \
				(int)fabs(data->player.pos.x - to_go[2].x))
				moving(&data->player, &to_go[1]);
			else
				moving(&data->player, &to_go[2]);
		}
		else if (can_he_move_to(&to_go[1], &data->map, &data->player))
			moving(&data->player, &to_go[1]);
		else if (can_he_move_to(&to_go[2], &data->map, &data->player))
			moving(&data->player, &to_go[2]);
	}
	player_in_grid(&data->map, &data->player);
	re_draw(data);
}

void	set_translater(int key_code, t_player *player, t_point *to_go)
{
	to_go[1].y = player->pos.y;
	to_go[1].x = player->pos.x;
	to_go[2].y = player->pos.y;
	to_go[2].x = player->pos.x;
	if (key_code == UP)
	{
		to_go[1].y += player->dir.y * 25;
		to_go[2].x += player->dir.x * 25;
	}
	else if (key_code == RIGHT)
	{
		to_go[1].y += player->sid.y * 25;
		to_go[2].x += player->sid.x * 25;
	}
	else if (key_code == DOWN)
	{
		to_go[1].y += -player->dir.y * 25;
		to_go[2].x += -player->dir.x * 25;
	}
	else if (key_code == LEFT)
	{
		to_go[1].y += -player->sid.y * 25;
		to_go[2].x += -player->sid.x * 25;
	}
}

char	can_he_move_to(t_point *to_go, t_map *map, t_player *player)
{
	size_t	i;
	size_t	j;
	int		space;

	space = GAP / 5;
	i = player->y - 1;
	while (i <= player->y + 1)
	{
		j = player->x - 1;
		while (j <= player->x + 1)
		{
			if ((int)to_go->y >= (int)map->grid[i][j].top_left.y - space && \
			(int)to_go->y <= (int)map->grid[i][j].bottom_right.y + space && \
				(int)to_go->x >= (int)map->grid[i][j].top_left.x - space && \
			(int)to_go->x <= (int)map->grid[i][j].bottom_right.x + space && \
				map->grid[i][j].c == '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	moving(t_player *player, t_point *to_go)
{
	player->pos.y = to_go->y;
	player->pos.x = to_go->x;
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
			if (is_pn_in_blk(&map->grid[i][j], &player->pos))
			{
				player->y = i;
				player->x = j;
				return ;
			}
		}
	}
}
