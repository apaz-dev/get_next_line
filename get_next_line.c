/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:58 by apaz-pri          #+#    #+#             */
/*   Updated: 2024/10/08 16:25:00 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != (unsigned char)c)
		if (!*str++)
			return (0);
	return ((char *)str);
}

char	*read_fd(int fd, char *fd_content)
{
	int		byte_read;
	char	*buff_tmp;

	buff_tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff_tmp)
		return (NULL);
	buff_tmp[0] = '\0';
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buff_tmp, BUFFER_SIZE);
		if (byte_read >= 1)
		{
			buff_tmp[byte_read] = '\0';
			fd_content = ft_strjoin(fd_content, buff_tmp);
		}
	}
	free(buff_tmp);
	if (byte_read < 0)
	{
		free(fd_content);
		return (NULL);
	}
	return (fd_content);
}

char	*get_first_line(char *text)
{
	char	*left;
	char	*line;

	left = ft_strchr(text, '\n');
	if (!left)
	{
		if (ft_strlen(text) >= 1)
		{
			left = ft_strchr(text, '\0');
			if (!left)
				return (NULL);
		}
		else
			return (NULL);
	}
	line = ft_substr(text, 0, (ft_strlen(text) - ft_strlen(left)) + 1);
	return (line);
}

char	*fill_text(char *text)
{
	char	*left;
	char	*tmp;
	int		l;

	left = ft_strchr(text, '\n');
	if (!left)
	{
		free (text);
		return (NULL);
	}
	else
		l = ft_strlen(left);
	tmp = ft_substr(text, (ft_strlen(text) - ft_strlen(left)) + 1, l + 1);
	free(text);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = read_fd(fd, text);
	if (text == NULL)
		return (NULL);
	line = get_first_line(text);
	text = fill_text(text);
	return (line);
}
