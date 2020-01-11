/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:00:12 by alpeliss          #+#    #+#             */
/*   Updated: 2020/01/11 15:48:04 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdio.h"

int main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		ret;

	if (ac < 2)
		return (0);
	line = NULL;
	fd = open(av[1], O_RDONLY);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		printf("[%d]->%s\n", ret, line);
		free(line);
	}
}

