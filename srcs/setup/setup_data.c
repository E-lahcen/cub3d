/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:29:42 by zwina             #+#    #+#             */
/*   Updated: 2022/08/08 17:06:10 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_data(t_data *data, char *filename)
{
	t_list	*file_content;

	file_content = read_filename(filename);
	setup_map(&data->map, file_content);
	setup_grid(&data->map, &data->player);
	print_map(&data->map);
	mlx_initializer(&data->mlx);
	ft_lstclear(&file_content, free);
}

t_list	*read_filename(char *filename)
{
	t_list	*file_content;
	char	*str;
	int		fd;

	extension_validation(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errors(filename, strerror(errno));
	file_content = NULL;
	str = get_next_line(fd);
	while (str)
	{
		ft_lstadd_back(&file_content, ft_lstnew(str));
		str = get_next_line(fd);
	}
	close(fd);
	remove_last_empty(file_content);
	return (file_content);
}

void	extension_validation(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 4)
		errors("Invalid extension", NULL);
	if (filename[len - 1] != 'b' && \
		filename[len - 2] != 'u' && \
		filename[len - 3] != 'c' && \
		filename[len - 4] != '.')
		errors("Invalid extension", NULL);
}

void	remove_last_empty(t_list *lst)
{
	t_list	*tmp;
	size_t	i;

	while (1)
	{
		tmp = ft_lstlast(lst);
		i = skip_begin_whitespaces(tmp->content, 1);
		if (((char *)tmp->content)[i] == '\0')
			ft_lstpop(lst);
		else
			break ;
	}
}

void	mlx_initializer(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
									&mlx->img.line_length, &mlx->img.endian);
}
