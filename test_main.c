/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:45:31 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/24 23:20:59 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Remove this file before publishing
*/

#include "ft_zlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	t_zstream	strm;
	long		test;
	t_uchar		ina[100];
	t_uchar		outa[120];
	int			fd;
	int			r;

	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
		return (-1);
	strm.available_out = 120;
	strm.next_in = ina;
	strm.next_out = outa;
	strm.total_read_out = 0;
	r = read(fd, ina, 100);
	close(fd);
	if (!(r > 0))
		return (-1);
	strm.available_in = r;
	strm.bitcnt = 0;
	strm.bitbuff = 0;
	ft_inflate(&strm, 0);
	if ((fd = open("TESTOUT", O_TRUNC | O_WRONLY)) <= 0)
		return (-1);
	write(fd, outa, strm.total_read_out);
	write(1, outa, strm.total_read_out);
	close(fd);
	printf("I exited normally\n");
	return (0);
}
