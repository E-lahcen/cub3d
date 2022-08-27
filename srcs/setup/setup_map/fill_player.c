/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:16:08 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 12:19:03 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	fill_player(t_player *player, t_block *block, size_t y, size_t x)
{
	player->y = y;
	player->x = x;
	player->pos.x = block->top_left.x + \
		(block->bottom_right.x - block->top_left.x) / 2;
	player->pos.y = block->top_left.y + \
		(block->bottom_right.y - block->top_left.y) / 2;
	if (block->c == 'N')
		player->angle = (3 * PI) / 2;
	if (block->c == 'E')
		player->angle = 0;
	if (block->c == 'S')
		player->angle = PI / 2;
	if (block->c == 'W')
		player->angle = PI;
	block->c = '0';
	fill_player_dir_sid(player);
}

void	fill_player_dir_sid(t_player *player)
{
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
	player->sid.x = cos(player->angle + PI / 2);
	player->sid.y = sin(player->angle + PI / 2);
}
