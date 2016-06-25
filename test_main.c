/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:45:31 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/25 21:57:40 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Remove this file before publishing
*/

#include "ft_zlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define AV_IN 2000
#define AV_OUT AV_IN * 2

int		main(int ac, char **av)
{
	t_zstream	strm;
	long		test;
	t_uchar		ina[AV_IN];
	t_uchar		outa[AV_OUT];
	int			fd;
	int			r;

	printf ("I started %d\n", ac);
	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
		return (-1);
	strm.available_out = AV_OUT;
	strm.next_in = ina;
	strm.next_out = outa;
	strm.total_read_out = 0;
	printf("read %d\n", r = read(fd, ina, AV_IN));
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
	printf("I exited normally %d\n", strm.errno);
	return (0);
}
