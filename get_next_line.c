/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:40:40 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/02 18:44:07 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*saved;
	static int	saved_len;
	int			nl_pos;
	char		*line;

	if (gnl_fill_buffer(fd, &saved, &saved_len) == -1)
		return (free(saved), saved = NULL, saved_len = 0, NULL);
	if (saved == NULL || saved[0] == '\0')
		return (NULL);
	nl_pos = gnl_has_nl(saved);
	line = gnl_extract_line(saved, nl_pos);
	saved = gnl_extract_rest(saved, nl_pos);
	if (nl_pos == -1)
		saved_len = 0;
	else
		saved_len = gnl_strlen(saved);
	return (line);
}
