/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:14 by zwina             #+#    #+#             */
/*   Updated: 2022/08/25 16:23:25 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_texture(t_mlx *mlx, t_map *map, char *str)
{
	char	*filename;
	int		i = 0;
	char	*tmp = str + 2 + skip_begin_whitespaces(str + 2, 1);

	while (tmp[i] != ' ' && tmp[i] != '\n' && tmp[i] != '\0' && tmp[i] != '\t')
		i++;

	filename = ft_substr(str, skip_begin_whitespaces(str + 2, 1) + 2, i);
	filename[ft_strlen(filename)] = '\0';
	if (!ft_strncmp(str, "NO", 2))
		get_img_texture(&map->no, filename, mlx->mlx);
	else if (!ft_strncmp(str, "EA", 2))
		get_img_texture(&map->ea, filename, mlx->mlx);
	else if (!ft_strncmp(str, "SO", 2))
		get_img_texture(&map->so, filename, mlx->mlx);
	else if (!ft_strncmp(str, "WE", 2))
		get_img_texture(&map->we, filename, mlx->mlx);
	free(filename);
}

void	*get_img_texture(t_txr *side, char *filename, void *mlx)
{
	side->img.img = mlx_xpm_file_to_image(mlx, filename, \
								&side->width, &side->height);
	if (side->img.img == NULL)
		errors("PROBLEM AT THE TEXTURE", NULL);
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
