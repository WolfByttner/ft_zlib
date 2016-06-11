/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_fixed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 01:36:54 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/05 21:05:40 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#define TMP_OUT "tmp.compressed"
#define MAX_BUFF 1000

/*
** in_buff is null terminated. It is capped for testing purposes
*/

int		deflate_stream(char *in_buff)
{
	int			fd2;
	z_stream	strm;
	char		out_buff[MAX_BUFF + 1];

	bzero(out_buff, sizeof (out_buff));
	if ((fd2 = open(TMP_OUT, O_WRONLY | O_CREAT)) <= 0)
		return (-1);
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.next_in = in_buff;
	strm.avail_in = strlen(in_buff);
	strm.avail_out = sizeof (out_buff);
	strm.next_out = out_buff;
	printf("Printing %d bytes\n", strlen(in_buff));
	deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
		15, 8, Z_FIXED);
	deflate(&strm, Z_FINISH);
	deflateEnd(&strm);
	write(fd2, out_buff, strlen(out_buff));
	close(fd2);
	return (0);
}

int		main(int ac, char **av)
{
	int			fd;
	char		buffer[MAX_BUFF + 1];

	printf("I started\n");
	if (ac < 2 || (fd = open(av[1], O_RDONLY)) <= 0 )
		return (0);
	printf("Opened file\n");
	bzero(buffer, sizeof (buffer));
	read(fd, buffer, MAX_BUFF);
	deflate_stream(buffer);
	close (fd);
}
