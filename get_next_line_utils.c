/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawgku-o <aawgku-o@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 03:35:40 by aawgku-o          #+#    #+#             */
/*   Updated: 2023/11/13 08:33:43 by aawgku-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*desttmp;
	size_t	i;

	if (dest == NULL && src == NULL)
	{
		return (dest);
	}
	i = 0;
	desttmp = dest;
	while (i < n)
	{
		*(unsigned char *)desttmp = *(unsigned char *)src;
		i++;
		desttmp++;
		src++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	if (size > len_src)
	{
		while (i < len_src)
			dst[i++] = 0;
		ft_memcpy(dst, src, len_src);
		dst[len_src] = 0;
	}
	else if (size != 0)
	{
		while (i < (size - 1))
			dst[i++] = 0;
		if (ft_strlen(src) < (size - 1))
			ft_memcpy(dst, src, ft_strlen(src));
		else
			ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = 0;
	}
	return (len_src);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = malloc(sizeof(*str) * len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, len);
	str[len] = 0;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;
	char	*ptr;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(*str) * len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = 0;
	ptr = str;
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	ptr = ptr + ft_strlen(s1);
	ft_memcpy(ptr, s2, ft_strlen(s2) + 1);
	return (str);
}
