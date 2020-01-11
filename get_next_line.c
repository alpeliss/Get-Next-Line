/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:53:40 by alpeliss          #+#    #+#             */
/*   Updated: 2020/01/11 18:58:55 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!(line = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	is_line(char *save)
{
	int	i;

	if (!save)
		return (0);
	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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

static char	*update_line(char *save)
{
	char	*new;
	int		i;
	int		j;

	if (!ft_strlen(save))
		return (0);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i++] != '\n')		
		return (0);
	if (!(new = (char *)malloc((ft_strlen(save) - i + 1) * sizeof(char))))
		return (0);
	j = 0;
	while (save[i + j])
	{
		new[j] = save[i + j];
		j++;
	}
	new[j] = '\0';
	free(save);
	return (new);
}

int			get_next_line(int fd, char **line)
{
	char		temp[BUFFER_SIZE + 1];
	static char	*save;
	int			lu;

	if (!line || read(fd, temp, 0) < 0)
		return (-1);
	*line = NULL;
	lu = 0;
	while (!is_line(save) && (lu = read(fd, temp, BUFFER_SIZE)))
	{
		if (!(save = super_join(save, temp, lu)))
			return (-1);
	}
	if (!(*line = get_line(save)))
		return (-1);
//	write(1, "1->", 3);
//	write(1, save, ft_strlen(save));
//	write(1, "<-\n", 3);
//	write(1, "2->", 3);
//	write(1, save, ft_strlen(save));
//	write(1, "<-\n\n---\n\n", 9);
	if ((save = update_line(save)))
		return (1);
	return (0);
}
