/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:00:12 by alpeliss          #+#    #+#             */
/*   Updated: 2020/01/16 17:21:04 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdio.h"
#include <limits.h>

int	main(int ac, char **av)
{
	char	*line;
	char	*gline;
	int		fd;
	int		gd;
	int		ret;
	int		gret;

	if (ac < 2)
		return (0);
	line = NULL;
	gline = NULL;
	fd = open(av[1], O_RDONLY);
	gd = open(av[2], O_RDONLY);
	printf("OPEN_MAX = %d\n", OPEN_MAX);
	ret = 1;
	gret = 1;
	while (ret > 0 || gret > 0)
	{
		ret = get_next_line(fd, &line);
		printf("[%d]->%s\n", ret, line);
		if (ret >= 0)
			free(line);
		gret = get_next_line(gd, &gline);
		printf("[%d]->%s\n", gret, gline);
		if (ret >= 0)
			free(gline);
	}
}
