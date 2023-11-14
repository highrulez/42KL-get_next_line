/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawgku-o <aawgku-o@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:35:15 by aawgku-o          #+#    #+#             */
/*   Updated: 2023/11/15 05:06:25 by aawgku-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	get_line_length(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}

static ssize_t	read_line(int fd, char *buffer)
{
	ssize_t	len_read;

	len_read = read(fd, buffer, BUFFER_SIZE);
	if (len_read > 0)
		buffer[len_read] = '\0';
	else
		buffer[0] = '\0';
	return (len_read);
}

static char	*extract_line(char *buffer, int fd, int *newline_found)
{
	ssize_t	len_read;
	char	*line;
	size_t	len_line;
	char	*buffer_temp;

	if (!(*buffer))
	{
		len_read = read_line(fd, buffer);
		if (len_read <= 0)
			return (NULL);
	}
	len_line = get_line_length(buffer);
	*newline_found = (buffer[len_line - 1] == '\n');
	line = malloc(len_line + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len_line + 1);
	buffer_temp = ft_strdup(buffer + len_line);
	if (!buffer_temp)
		return (NULL);
	ft_strlcpy(buffer, buffer_temp, ft_strlen(buffer_temp) + 1);
	free(buffer_temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			newline_found;
	char		*current_line;
	char		*new_line;
	char		*temp;

	newline_found = 0;
	if (fd < 0)
		return (NULL);
	newline_found = 0;
	current_line = extract_line(buffer, fd, &newline_found);
	if (!current_line)
		return (NULL);
	while (!newline_found)
	{
		new_line = extract_line(buffer, fd, &newline_found);
		if (!new_line)
			return (current_line);
		temp = current_line;
		current_line = ft_strjoin(current_line, new_line);
		free(temp);
		free(new_line);
	}
	return (current_line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);

// 	printf("\n****FD****\n");
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	system("leaks -q a.out");
// 	return (0);
// }
