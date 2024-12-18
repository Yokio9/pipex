/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:47:33 by dimatayi          #+#    #+#             */
/*   Updated: 2024/10/10 16:42:34 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new_elem;

	while (*lst)
	{
		new_elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = new_elem;
	}
	*lst = NULL;
}
