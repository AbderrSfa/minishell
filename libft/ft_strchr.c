/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:52:11 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/29 15:27:44 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	str;

	i = 0;
	str = c;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != str)
		i++;
	if (s[i] == str)
		return ((char *)&s[i]);
	return (NULL);
}
