/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:44:50 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/06/21 19:13:25 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get(char **line, t_get *s, char *c, t_get **d)
{
	c = ft_calloc(1, 1);
	while (s->tab[(s->n)] != '\n')
	{
		if (s->tab[s->n] == '\0')
		{
			ft_bzero(s->tab, s->n);
			s->i = read(s->fd, s->tab, BUFFER_SIZE);
			s->n = 0;
		}
		if (s->i == 0)
			*line = c;
		if (s->i < 0)
			free(c);
		if (s->i < 1)
			return (free_list(d, s, s->i));
		c = ft_strjoin_free(c, s->tab + s->n);
		while (s->tab[s->n] != '\n' && s->tab[s->n] != '\0')
			s->n++;
	}
	s->n++;
	*line = c;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_get	*debut;
	t_get			*p;

	p = debut;
	while (p != NULL && p->fd != fd)
		p = p->next;
	if (p == NULL)
	{
		p = malloc(sizeof(t_list));
		p->tab = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!p->tab)
		{
			free(p);
			return (-1);
		}
		p->fd = fd;
		p->n = 0;
		p->next = debut;
		debut = p;
	}
	return (get(line, p, NULL, &debut));
}

int	free_list(t_get **d, t_get *f, int i)
{
	t_get	*p;

	p = *d;
	while (p != f && p->next != f)
		p = p->next;
	if (p == f)
		*d = f->next;
	else
		p->next = f->next;
	free(f->tab);
	free(f);
	return (i);
}
