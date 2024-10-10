/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:27:20 by apaz-pri          #+#    #+#             */
/*   Updated: 2024/10/08 16:28:53 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	c;

	if (!str)
		return (0);
	c = 0;
	while (*str != '\0')
	{
		c++;
		str++;
	}
	return (c);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	i2;

	if (!s1)
	{
		s1 = ft_alloc(sizeof(char), 1);
		if (!s1)
			return (NULL);
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i2 = -1;
	while (s2[++i2])
		str[i + i2] = s2[i2];
	str[i + i2] = '\0';
	free(s1);
	return (str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s;

	s = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*substr;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (len > str_len - start)
		len = str_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

void	*ft_alloc(size_t count, size_t size)
{
	void	*ptr;
	char	*ptr_tmp;
	size_t	i;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	i = 0;
	ptr_tmp = (char *)ptr;
	while (i < (size * count))
		ptr_tmp[i++] = '\0';
	return (ptr);
}
