/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:13:46 by zwina             #+#    #+#             */
/*   Updated: 2022/08/06 11:40:50 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL || lst->next == NULL)
		return ;
	tmp = lst;
	while (tmp->next->next)
		tmp = tmp->next;
	ft_lstdelone(tmp->next, free);
	tmp->next = NULL;
}
