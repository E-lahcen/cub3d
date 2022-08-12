/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_look.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:08:13 by zwina             #+#    #+#             */
/*   Updated: 2022/08/07 19:08:40 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_look(int key_code, t_data *data)
{
	if (key_code == LOOK_RIGHT)
	{
		data->player.angle += PI / 32;
		if (data->player.angle > 2 * PI)
			data->player.angle = PI / 32;
		fill_player_dir_sid(&data->player);
	}
	else if (key_code == LOOK_LEFT)
	{
		data->player.angle -= PI / 32;
		if (data->player.angle < 0)
			data->player.angle = 2 * PI - PI / 32;
		fill_player_dir_sid(&data->player);
	}
	re_draw(data);
}
