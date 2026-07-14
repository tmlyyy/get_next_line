/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:56:45 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/14 16:56:47 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_strlen(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, int len1, char *s2, int len2)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			new_str[i] = s1[i];
		else
			new_str[i] = s2[i - len1];
		i++;
	}
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

int	gnl_has_nl(char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_fill_buffer(int fd, char **saved)
{
	char	*buffer;
	int		bytes_read;
	int		found;

	found = (gnl_has_nl(*saved) != -1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (-1);
	bytes_read = 1;
	while (!found && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), -1);
		buffer[bytes_read] = '\0';
		*saved = gnl_strjoin(*saved, gnl_strlen(*saved), buffer, bytes_read);
		found = (gnl_has_nl(buffer) != -1);
	}
	free(buffer);
	return (0);
}
