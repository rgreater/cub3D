/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:41:30 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/12 21:48:26 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el;

	if (!(el = malloc(sizeof(t_list))))
		return (0);
	el->content = content;
	el->next = 0;
	return (el);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*el;

	if (!lst)
		return (0);
	el = lst;
	while (el->next)
		el = el->next;
	return (el);
}

int		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*el;

	if (!lst || !new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	el = ft_lstlast(*lst);
	el->next = new;
	return (0);
}

int		ft_lstdestroy(t_list **lst, int free_content)
{
	t_list	*el;
	t_list	*tmp;

	if (!lst || !*lst)
		return (-1);
	el = *lst;
	while (el)
	{
		tmp = el->next;
		if (free_content && el->content)
			free(el->content);
		el->content = 0;
		el->next = 0;
		free(el);
		el = tmp;
	}
	return (0);
}
