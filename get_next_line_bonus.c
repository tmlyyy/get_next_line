/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:56:14 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/14 16:56:19 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_extract_line(char *s, int nl_pos)
{
	char	*line;
	int		len;
	int		i;

	if (nl_pos == -1)
		len = gnl_strlen(s);
	else
		len = nl_pos + 1;
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_extract_rest(char *s, int nl_pos)
{
	char	*rest;
	int		len;
	int		i;

	if (nl_pos == -1)
		return (free(s), NULL);
	len = gnl_strlen(s);
	rest = malloc(sizeof(char) * (len - nl_pos));
	if (rest == NULL)
		return (free(s), NULL);
	i = 0;
	while (nl_pos + 1 + i < len)
	{
		rest[i] = s[nl_pos + 1 + i];
		i++;
	}
	rest[i] = '\0';
	free(s);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	int			nl_pos;
	char		*line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (gnl_fill_buffer(fd, &saved[fd]) == -1)
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	if (saved[fd] == NULL || saved[fd][0] == '\0')
		return (NULL);
	nl_pos = gnl_has_nl(saved[fd]);
	line = gnl_extract_line(saved[fd], nl_pos);
	saved[fd] = gnl_extract_rest(saved[fd], nl_pos);
	return (line);
}
