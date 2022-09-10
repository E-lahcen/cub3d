/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:03:08 by lelhlami          #+#    #+#             */
/*   Updated: 2022/09/06 11:38:43 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_data *data)
{
	int		i;

	i = -1;
	data->map.mini_map = (char **)malloc(sizeof(char *) * 15);
	if (!data->map.mini_map)
		errors("Error in allocation with malloc", NULL);
	while (++i < 15)
		data->map.mini_map[i] = (char *)malloc(sizeof(char) * 15);
	set_mini_map(data);
	mini_setup_grid(data);
	draw_mini_map_player(data);
	free_double(data);
}

void	draw_mini_map_player(t_data *data)
{
	t_point	p1;
	t_point	p2;

	p1.x = MINIMAPSTART_X;
	p1.y = MINIMAPSTART_Y;
	while (p1.y < SCREENHEIGHT - 50)
	{
		p1.x = MINIMAPSTART_X;
		while (p1.x < MINIMAPSTART_X + MINIMAPWIDTH)
		{
			p2.x = (p1.x - (MINIMAPSTART_X + MINIMAPWIDTH / 2)) \
			* cos(-data->player.angle - PI / 2) - (p1.y - (MINIMAPSTART_Y \
			+ MINIMAPHEIGHT / 2)) * sin(-data->player.angle - PI / 2) + \
			(MINIMAPSTART_X + MINIMAPWIDTH / 2);
			p2.y = (p1.x - (MINIMAPSTART_X + MINIMAPWIDTH / 2)) \
			* sin(-data->player.angle - PI / 2) + (p1.y - (MINIMAPSTART_Y \
			+ MINIMAPHEIGHT / 2)) * cos(-data->player.angle - PI / 2) + \
			(MINIMAPSTART_Y + MINIMAPHEIGHT / 2);
			draw_mini_blocks(data, p1, p2);
			p1.x++;
		}
		p1.y++;
	}
}
\

void	draw_mini_blocks(t_data *data, t_point p1, t_point p2)
{
	size_t	i;
	size_t	j;

	p1.x = p1.x - MINIMAPSTART_X;
	p1.y = p1.y - (MINIMAPSTART_Y);
	i = -1;
	while (++i < 15)
	{
		j = -1;
		while (++j < 15)
		{
			if (is_pn_in_blk(&data->map.mini_grid[i][j], &p1) && verify_in_circle(p2.x, p2.y))
			{
				if (data->map.mini_map[i][j] == '1')
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 0);
				else if (data->map.mini_map[i][j] == '2')
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 8421204);
				else if (data->map.mini_map[i][j] == '0')
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 8421504);
				else if (is_player(data->map.mini_map[i][j]))
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 255);
				else if (data->map.mini_map[i][j] == '3')
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 100);
				return ;
			}
		}
	}
}

int	verify_in_circle(double x, double y)
{
	t_point player_pos;
	t_point this_point;

	this_point.x = x;
	this_point.y = y;
	player_pos.x = (MINIMAPSTART_X) + MINIMAPWIDTH / 2;
	player_pos.y = (MINIMAPSTART_Y) + MINIMAPHEIGHT / 2;
	if (distance(&this_point, &player_pos) > 100)
		return (0);
	return(1);
}
