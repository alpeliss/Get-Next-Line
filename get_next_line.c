/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:53:40 by alpeliss          #+#    #+#             */
/*   Updated: 2020/01/16 21:02:42 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save && save[i] && save[i] != '\n')
		i++;
	if (!(line = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (save && save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*super_join(char *save, char *temp, int lu)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = (char *)malloc((ft_strlen(save) + lu + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (save && save[i])
	{
		new[i] = save[i];
		i++;
	}
	j = 0;
	while (j < lu)
	{
		new[i + j] = temp[j];
		j++;
	}
	new[i + j] = '\0';
	if (save)
		free(save);
	return (new);
}

static char	*update_line(char *save, int *lu)
{
	char	*new;
	int		i;
	int		j;

	*lu = 0;
	if (!save)
		return (save);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if ((!save[i++])
		|| (!(new = (char *)malloc((ft_strlen(save) - i + 1) * sizeof(char)))))
	{
		free(save);
		if (save[i - 1])
			*lu = -1;
		return (0);
	}
	j = -1;
	while (save[i + ++j])
		new[j] = save[i + j];
	new[j] = '\0';
	free(save);
	return (new);
}

static int	get_next_l(int fd, char **line, unsigned int buff)
{
	char		temp[buff + 1];
	static char	*save[OPEN_MAX];
	int			lu;

	if (!line || read(fd, temp, 0) < 0)
		return (-1);
	*line = NULL;
	lu = 0;
	while (!is_line(save[fd]) && (lu = read(fd, temp, buff)))
		if (!(save[fd] = super_join(save[fd], temp, lu)))
			return (-1);
	if (!(*line = get_line(save[fd])))
		return (-1);
	save[fd] = update_line(save[fd], &lu);
	if (!save[fd])
		return (lu);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	unsigned int	buff;

	if (BUFFER_SIZE <= 0)
		return (-1);
	buff = BUFFER_SIZE;
	return (get_next_l(fd, line, buff));
}
