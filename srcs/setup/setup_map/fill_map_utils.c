/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 10:38:39 by zwina             #+#    #+#             */
/*   Updated: 2022/08/20 20:19:55 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	filling_map(char *map_line, char *file_line, size_t size)
{
	size_t	i;

	i = 0;
	while (file_line[i] && i < size)
	{
		if (file_line[i] == ' ' || file_line[i] == '\n')
			map_line[i] = '\0';
		else
			map_line[i] = file_line[i];
		i++;
	}
	while (i < size)
		map_line[i++] = '\0';
}

size_t	skip_begin_whitespaces(char *str, char with_tab)
{
	size_t	i;

	i = 0;
	while (str[i] && \
		(str[i] == ' ' || (with_tab && str[i] == '\t') || str[i] == '\n'))
		i++;
	return (i);
}

size_t	skip_end_whitespaces(char *str, char with_tab)
{
	size_t	i;

	i = ft_strlen(str);
	while (i > 0 && \
		(str[i] == '\0' || str[i] == '\n' || str[i] == ' ' || \
		(with_tab && str[i] == '\t')))
		i--;
	return (i + 1);
}
