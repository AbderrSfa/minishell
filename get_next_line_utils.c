/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:45:14 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/06/21 19:13:05 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_strjoin_free(char *a, char *b)
{
	char	*c;
	size_t	la;
	size_t	lb;

	la = 0;
	while (a[la] != '\0')
		la++;
	lb = 0;
	while (b[lb] != '\n' && b[lb] != '\0')
		lb++;
	c = ft_calloc(la + lb + 1, 1);
	if (!c)
		return (NULL);
	while (lb--)
		c[la + lb] = b[lb];
	while (la--)
		c[la] = a[la];
//	free(a);
	return (c);
}
