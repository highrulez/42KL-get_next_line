/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawgku-o <aawgku-o@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 03:35:29 by aawgku-o          #+#    #+#             */
/*   Updated: 2023/11/15 05:01:47 by aawgku-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	get_line_length(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}

static ssize_t	read_line(int fd, char **buffer)
{
	ssize_t	len_read;

	free(*buffer);
	*buffer = malloc(sizeof(**buffer) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (0);
	len_read = read(fd, *buffer, BUFFER_SIZE);
	if (len_read <= 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	else
		(*buffer)[len_read] = 0;
	return (len_read);
}

static char	*extract_line(char **buffer, int fd, int *nl_found)
{
	ssize_t	len_read;
	char	*line;
	size_t	len_line;
	char	*buff_tmp;

	if (*buffer == NULL || ft_strlen(*buffer) == 0)
	{
		len_read = read_line(fd, buffer);
		if (len_read <= 0)
			return (NULL);
	}
	len_line = get_line_length(*buffer);
	if ((*buffer)[len_line - 1] == '\n')
		*nl_found = 1;
	line = malloc(len_line + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, *buffer, len_line + 1);
	buff_tmp = ft_strdup((*buffer) + len_line);
	if (buff_tmp == NULL)
		return (NULL);
	free(*buffer);
	*buffer = buff_tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line_old;
	int			nl_found;
	char		*line;
	char		*new_line;

	if (fd < 0)
		return (NULL);
	nl_found = 0;
	line = extract_line(&buffer[fd], fd, &nl_found);
	if (line == NULL)
		return (NULL);
	while (nl_found == 0)
	{
		new_line = extract_line(&buffer[fd], fd, &nl_found);
		if (new_line == NULL)
			return (line);
		line_old = line;
		line = ft_strjoin(line, new_line);
		free(new_line);
		free(line_old);
	}
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd;
// 	int fd2;
// 	int fd3;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	fd3 = open("test3.txt", O_RDONLY);

// 	printf("\n****FD 1****\n");
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);

// 	printf("\n****FD 2****\n");
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// 	line = get_next_line(fd2);
// 	printf("%s\n", line);
// 	free(line);

// 	printf("****FD 3****\n");
// 	line = get_next_line(fd3);
// 	printf("%s", line);
// 	line = get_next_line(fd3);
// 	printf("%s", line);
// 	line = get_next_line(fd3);
// 	printf("%s", line);
// 	line = get_next_line(fd3);
// 	printf("%s\n", line);
// 	free(line);

// 	system("leaks -q a.out");
// 	return (0);
// }
