/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:59:08 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/02 17:37:02 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **content)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (0);
	;
	p->next = 0;
	return (p);
}
