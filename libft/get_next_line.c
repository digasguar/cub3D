/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiahidal <oiahidal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:14:31 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/11 16:06:56 by oiahidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (free(ptr), NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		if (s2[j++] == '\n')
			break ;
	}
	ptr[i] = '\0';
	return (free(s1), ptr);
}

int	search_for(const char *s, char c)
{
	unsigned int	i;
	unsigned int	len;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	update_buffer(char *buff)
{
	int		i;
	int		j;

	j = search_for(buff, '\n');
	if (j == -1)
		return ;
	i = 0;
	j++;
	while (buff[i + j])
	{
		buff[i] = buff[i + j];
		i++;
	}
	buff[i] = '\0';
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strjoin_mod(NULL, buffer);
	read_bytes = 1;
	while (read_bytes > 0 && search_for(line, '\n') == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		buffer[read_bytes] = '\0';
		line = ft_strjoin_mod(line, buffer);
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	return (update_buffer(buffer), line);
}

/* #include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("test10.txt", O_RDONLY);
	if (fd < 0)
		return (printf("Error al abrir el archivo\n"), 1);
	char *line;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 0;
} */
