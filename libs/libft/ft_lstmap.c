/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:33 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/01/25 17:50:33 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*save;

	if (!lst || !f || !del)
		return (0);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (0);
	save = newlst;
	lst = lst->next;
	while (lst)
	{
		newlst->next = ft_lstnew(f(lst->content));
		if (!newlst->next)
		{
			del(newlst->content);
			ft_lstclear(&save, del);
			return (0);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	newlst->next = NULL;
	return (save);
}
