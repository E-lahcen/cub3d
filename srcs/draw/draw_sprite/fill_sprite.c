/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:23:57 by lelhlami          #+#    #+#             */
/*   Updated: 2022/09/04 12:55:19 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_img_sprite(t_sprite *spr, char *filename, void *mlx)
{
	spr->img.img = mlx_xpm_file_to_image(mlx, filename, \
								(int *)&spr->width, (int *)&spr->height);
	if (spr->img.img == NULL)
		errors("PROBLEM AT THE SPRITE", NULL);
	spr->img.addr = mlx_get_data_addr(spr->img.img, \
										&spr->img.bits_per_pixel, \
										&spr->img.line_length, \
										&spr->img.endian);
}
