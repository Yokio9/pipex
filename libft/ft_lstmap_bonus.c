/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:47:43 by dimatayi          #+#    #+#             */
/*   Updated: 2024/10/10 17:00:13 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_elem(t_list *elem, t_list *first_elem, void (*del)(void *))
{
	while (first_elem)
	{
		elem = first_elem;
		first_elem = (first_elem)->next;
		del(elem);
		free(elem);
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*first_elem;
	void	*new_content;

	if (!lst)
		return (NULL);
	first_elem = ft_lstnew(f(lst->content));
	if (!first_elem)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_content = f(lst->content);
		elem = ft_lstnew(new_content);
		if (!elem)
		{
			del(new_content);
			free_elem(first_elem, elem, del);
			return (NULL);
		}
		ft_lstadd_back(&first_elem, elem);
		lst = lst->next;
	}
	return (first_elem);
}
