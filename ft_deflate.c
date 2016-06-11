/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 18:58:52 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 12:59:13 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_zlib_detail.h"
#include <strings.h>
#include <limits.h>

extern int	ft_deflate(t_zstreamp strm, int flush)
{
		t_ulong	bits;
		unsigned char	arr[10] = { 6, 16 + 6, 32};
	int fd = open("IAMTEST", O_TRUNC | O_WRONLY);

		strm->errno = 0;
	strm->next_in = arr;
		strm->bitbuff = 0;
		strm->bitcnt = 0;
	strm->available_in = 10;
	get_bits(4, strm);
	printf("Short btrak\n");
	bits = get_bits(16, strm);
	long	foo = ((~0L));// - (1L << 63));
	//foo -= 65535 - 255;
	foo = foo << 4;
write(fd, &bits, sizeof(bits));


	printf("bits is %ld | errno is | %d|\n", bits, strm->errno);
	printf("%lu|%lu\n", foo, CHAR_BIT * sizeof (long));
	close(fd);
	return (flush);
}
