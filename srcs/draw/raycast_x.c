/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:31 by zwina             #+#    #+#             */
/*   Updated: 2022/09/03 12:16:44 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_x(t_ray *ray, t_map *map, t_player *player, double r_angle)
{
	ray->y = player->y;
	ray->x = player->x;
	ray->rp.y = player->pos.y;
	ray->rp.x = player->pos.x;
	if ((r_angle >= 0 && r_angle < PI / 2) || \
			(r_angle > (3 * PI) / 2 && r_angle <= 2 * PI))
		raycast_x_right(ray, map, player, r_angle);
	else if (r_angle > PI / 2 && r_angle < (3 * PI) / 2)
		raycast_x_left(ray, map, player, r_angle);
}

void	raycast_x_right(t_ray *ray, t_map *map, t_player *player, \
						double r_angle)
{
	double	dy;
	double	dx;

	while (ray->rp.y > 0 && ray->rp.y < map->height * GAP && \
							ray->x < map->width)
	{
		dx = map->grid[ray->y][ray->x].bottom_right.x - ray->rp.x;
		ray->rp.x += dx;
		dy = -tan(2 * PI - r_angle) * fabs(dx);
		ray->rp.y += dy;
		ray->dis = distance(&player->pos, &ray->rp);
		if (ray_hit_x(map, ray, RIGHT))
			break ;
		ray->x += 1;
	}
}

void	raycast_x_left(t_ray *ray, t_map *map, t_player *player, \
						double r_angle)
{
	double	dy;
	double	dx;

	while (ray->rp.y > 0 && ray->rp.y < map->height * GAP && ray->x > 0)
	{
		dx = map->grid[ray->y][ray->x].top_left.x - ray->rp.x;
		ray->rp.x += dx;
		dy = -tan(r_angle) * fabs(dx);
		ray->rp.y += dy;
		ray->dis = distance(&player->pos, &ray->rp);
		if (ray_hit_x(map, ray, LEFT))
			break ;
		ray->x -= 1;
	}
}

char	ray_hit_x(t_map *map, t_ray *ray, char side)
{
	size_t	i;
	int		offset;

	offset = 0;
	if (side == RIGHT)
		offset = 1;
	else if (side == LEFT)
		offset = -1;
	if (ray->x + offset >= map->width)
		return (1);
	i = -1;
	while (++i < map->height)
		if (is_pn_in_blk(&map->grid[i][ray->x + offset], &ray->rp) && \
			(map->grid[i][ray->x + offset].c == '1' \
			|| map->grid[i][ray->x + offset].c == '3'))
			return (1);
	return (0);
}
