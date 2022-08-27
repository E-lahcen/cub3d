/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:31 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 11:55:35 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_y(t_ray *ray, t_map *map, t_player *player, double r_angle)
{
	ray->y = player->y;
	ray->x = player->x;
	ray->rp.y = player->pos.y;
	ray->rp.x = player->pos.x;
	if (r_angle > PI && r_angle < 2 * PI)
	{
		raycast_y_up(ray, map, player, r_angle);
	}
	else if (r_angle > 0 && r_angle < PI)
		raycast_y_down(ray, map, player, r_angle);
}

void	raycast_y_up(t_ray *ray, t_map *map, t_player *player, \
					double r_angle)
{
	double	dy;
	double	dx;

	while (ray->rp.x > 0 && ray->rp.x < map->width * GAP && ray->y > 0)
	{
		dy = map->grid[ray->y][ray->x].top_left.y - ray->rp.y;
		ray->rp.y += dy;
		dx = -tan(2 * PI - r_angle - PI / 2) * fabs(dy);
		ray->rp.x += dx;
		ray->dis = distance(&player->pos, &ray->rp);
		if (ray_hit_y(map, ray, UP))
			break ;
		ray->y -= 1;
	}
}

void	raycast_y_down(t_ray *ray, t_map *map, t_player *player, \
						double r_angle)
{
	double	dy;
	double	dx;

	while (ray->rp.x > 0 && ray->rp.x < map->width * GAP && \
							ray->y < map->height)
	{
		dy = map->grid[ray->y][ray->x].bottom_right.y - ray->rp.y;
		ray->rp.y += dy;
		dx = -tan(r_angle - PI / 2) * fabs(dy);
		ray->rp.x += dx;
		ray->dis = distance(&player->pos, &ray->rp);
		if (ray_hit_y(map, ray, DOWN))
			break ;
		ray->y += 1;
	}
}

char	ray_hit_y(t_map *map, t_ray *ray, char side)
{
	size_t	i;
	int		offset;

	offset = 0;
	if (side == UP)
		offset = -1;
	else if (side == DOWN)
		offset = 1;
	if (ray->y + offset >= map->height)
		return (1);
	i = -1;
	while (++i < map->width)
		if (is_pn_in_blk(&map->grid[ray->y + offset][i], &ray->rp) && \
			map->grid[ray->y + offset][i].c == '1')
			return (1);
	return (0);
}
