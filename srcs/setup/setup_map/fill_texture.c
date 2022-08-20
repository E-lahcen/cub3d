/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:14 by zwina             #+#    #+#             */
/*   Updated: 2022/08/13 15:11:43 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_texture(t_mlx *mlx, t_map *map, char *str)
{
	void	*img;
	char	*filename;

	filename = ft_strdup(str + 2 + skip_begin_whitespaces(str + 2, 1));
	filename[ft_strlen(filename) - 1] = '\0';
	img = NULL;
	if (!ft_strncmp(str, "NO", 2))
		img = get_img_texture(&map->no, filename, mlx->mlx);
	else if (!ft_strncmp(str, "EA", 2))
		img = get_img_texture(&map->ea, filename, mlx->mlx);
	else if (!ft_strncmp(str, "SO", 2))
		img = get_img_texture(&map->so, filename, mlx->mlx);
	else if (!ft_strncmp(str, "WE", 2))
		img = get_img_texture(&map->we, filename, mlx->mlx);
	free(filename);
	if (img == NULL)
		errors("PROBLEM AT THE TEXTURE", NULL);
}

void	*get_img_texture(t_txr *side, char *filename, void *mlx)
{
	side->img.img = mlx_xpm_file_to_image(mlx, filename, \
								&side->width, &side->height);
	side->img.addr = mlx_get_data_addr(side->img.img, \
										&side->img.bits_per_pixel, \
										&side->img.line_length, \
										&side->img.endian);
	return (side->img.img);
}

void	texture_validation(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = skip_begin_whitespaces(str, 1);
	j = skip_end_whitespaces(str, 1);
	tmp = ft_substr(str, i, j - i);
	if (access(tmp, R_OK) == -1)
		errors("PROBLEM AT THE TEXTURE'S PATH", NULL);
	free(tmp);
}
