/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:03:08 by lelhlami          #+#    #+#             */
/*   Updated: 2022/08/29 17:18:55 by lelhlami         ###   ########.fr       */
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
	set_circle(data, circle);
	while (p1.y < SCREENHEIGHT - 50)
	{
		p1.x = SCREENWIDTH / 10;
		while (p1.x < SCREENWIDTH / 10 + MINIMAPWIDTH)
		{
			p2.x = p1.x * cos(data->player.angle) - p1.y * sin(data->player.angle);
			p2.y = p1.x * sin(data->player.angle) + p1.y * cos(data->player.angle);
			draw_mini_blocks(data, p1, p1, circle);
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
			if (is_pn_in_blk(&data->map.mini_grid[i][j], &p) && verify_in_circle(circle, p2.x, p2.y) == 1)
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

void	set_circle(t_data *data, t_point *circle)
{
	int	i;

	i = -1;
	while (++i < 360)
	{
		circle[i].x = SCREENWIDTH / 10 + 105 + 100 * cos(i * PI / 180);
		circle[i].y = SCREENHEIGHT - 260  + 105 + 100 * sin(i * PI / 180);
		my_mlx_pixel_put(&data->mlx.img, circle[i].x, circle[i].y, 0);
	}
}	

int	verify_in_circle(t_point *circle, double x, double y)
{
	int i;

	i = -1;
	while (++i < 180)
	{
		if (i < 90 && x < circle[i].x)
			return (printf("here 1\n"));
		if (i >= 90 && x > circle[i].x)
			return (printf("here 2\n"));
		if (y > circle[i].y)
			return (printf("here 3  y = %f | circle[%d] = %f\n", y, i, circle[i].y));
	}
	i -= 1;
	while (++i < 360)
	{
		if (i < 270 && x > circle[i].x)
			return (printf("here 4\n"));
		if (i >= 270 && x < circle[i].x)
			return (printf("here 5\n"));
		if (y < circle[i].y)
			return (printf("here 6\n"));
	}
	return (1);
}
