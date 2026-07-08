/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:41:09 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/02 17:53:06 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, int len1, char *s2, int len2);
int		gnl_has_nl(char *s);
char	*gnl_extract_line(char *s, int nl_pos);
char	*gnl_extract_rest(char *s, int nl_pos);
int		gnl_fill_buffer(int fd, char **saved, int *saved_len);

#endif