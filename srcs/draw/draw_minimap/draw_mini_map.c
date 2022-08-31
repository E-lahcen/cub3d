/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:03:08 by lelhlami          #+#    #+#             */
/*   Updated: 2022/08/31 14:22:16 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_map(t_data *data)
{
	int		i;

	i = -1;
	data->map.mini_map = (char **)malloc(sizeof(char *) * 21);
	if (!data->map.mini_map)
		errors("Error in allocation with malloc", NULL);
	while (++i < 21)
		data->map.mini_map[i] = (char *)malloc(sizeof(char) * 21);
	set_mini_map(data);
	mini_setup_grid(data);
	draw_mini_map_player(data);
	free_double(data);
}

void	draw_mini_map_player(t_data *data)
{
	t_point	p1;
	t_point	p2;
	t_point circle[360];

	p1.x = SCREENWIDTH / 10;
	p1.y = SCREENHEIGHT - 260;
	while (p1.y < SCREENHEIGHT - 50)
	{
		p1.x = SCREENWIDTH / 10;
		while (p1.x < SCREENWIDTH / 10 + MINIMAPWIDTH)
		{
			p2.x = (p1.x - (SCREENWIDTH / 10 + MINIMAPWIDTH / 2)) * cos(data->player.angle - 3 * PI / 2) - (p1.y - (SCREENHEIGHT - 260 + MINIMAPHEIGHT / 2)) * sin(data->player.angle - 3 * PI / 2) + (SCREENWIDTH / 10 + MINIMAPWIDTH / 2);
			p2.y = (p1.x - (SCREENWIDTH / 10 + MINIMAPWIDTH / 2)) * sin(data->player.angle - 3 * PI / 2) + (p1.y - (SCREENHEIGHT - 260 + MINIMAPHEIGHT / 2)) * cos(data->player.angle - 3 * PI / 2) + (SCREENHEIGHT - 260 + MINIMAPHEIGHT / 2);
			// printf("p2.x = %f\n", p2.x);
			draw_mini_blocks(data, p1, p2, circle);
			p1.x++;
		}
		p1.y++;
	}
}

void	draw_mini_blocks(t_data *data, t_point p1, t_point p2, t_point *circle)
{
	t_point	p;
	size_t	i;
	size_t	j;
	p.x = p1.x - SCREENWIDTH / 10;
	p.y = p1.y - (SCREENHEIGHT - 260);
	i = -1;
	(void)circle;
	while (++i < 21)
	{
		j = -1;
		while (++j < 21)
		{
			if (is_pn_in_blk(&data->map.mini_grid[i][j], &p) && verify_in_circle(p2.x, p2.y))
			{
				if (data->map.mini_map[i][j] == '1')
				{
					// printf("here 1\n");
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 0);
				}
				else if (data->map.mini_map[i][j] == '2')
				{
					// printf("here 1\n");
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 16711680);
				}
				else if (data->map.mini_map[i][j] == '0')
				{
					// printf("here 0\n");
					my_mlx_pixel_put(&data->mlx.img, p2.x, p2.y, 8421504);
				}
				else if (is_player(data->map.mini_map[i][j]))
				{
					// printf("here player\n");
					my_mlx_pixel_put(&data->mlx.img, p1.x, p1.y, 255);
				}
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
	player_pos.x = (SCREENWIDTH / 10) + MINIMAPWIDTH / 2;
	player_pos.y = (SCREENHEIGHT - 260) + MINIMAPHEIGHT / 2;
	if (distance(&this_point, &player_pos) > 100)
		return (0);
	return(1);
}
