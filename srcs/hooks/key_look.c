/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_look.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:08:13 by zwina             #+#    #+#             */
/*   Updated: 2022/08/31 19:04:31 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_look(int key_code, t_data *data)
{
	double	rotate;

	rotate = PI / 30;
	if (key_code == LOOK_RIGHT)
	{
		data->player.angle += rotate;
		if (data->player.angle > 2 * PI)
			data->player.angle = rotate;
		fill_player_dir_sid(&data->player);
	}
	else if (key_code == LOOK_LEFT)
	{
		data->player.angle -= rotate;
		if (data->player.angle < 0)
			data->player.angle = 2 * PI - rotate;
		fill_player_dir_sid(&data->player);
	}
	re_draw(data);
}
