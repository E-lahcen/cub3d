/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:50:58 by zwina             #+#    #+#             */
/*   Updated: 2022/08/07 18:39:00 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hooks(int key_code, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key_code == 53)
		exit(0);
	else if (key_code == UP || key_code == RIGHT || \
			key_code == DOWN || key_code == LEFT)
		move(key_code, data);
	else if (key_code == LOOK_RIGHT || key_code == LOOK_LEFT)
		key_look(key_code, data);
	else if (key_code == 35)
	{
		printf("player angle == %f\n", data->player.angle);
		printf("player dir.y == %f\n", data->player.dir.y);
		printf("player dir.x == %f\n", data->player.dir.x);
	}
	return (0);
}

void	re_draw(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img.img);
	data->mlx.img.img = \
		mlx_new_image(data->mlx.mlx, SCREENWIDTH, SCREENHEIGHT);
	data->mlx.img.addr = \
		mlx_get_data_addr(data->mlx.img.img, \
						&data->mlx.img.bits_per_pixel, \
						&data->mlx.img.line_length, \
						&data->mlx.img.endian);
	draw(data);
}
