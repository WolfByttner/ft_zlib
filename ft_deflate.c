/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 18:58:52 by jbyttner          #+#    #+#             */
/*   Updated: 2016/07/13 00:26:41 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_zlib_detail.h"
#include <strings.h>
#include <limits.h>
#define FT_ZCHUNK 32768
#define FT_ZFINISH 1
#define FT_ZHASHSIZE 300
#define FT_ZMAXLEN 258


static int	ft_deflate_match_str(const t_byte *start, const t_byte *end,
		t_uint avail)
{
	size_t	a;
	size_t	len;

	len = 0;
	a = 0;
	while (len < FT_ZMAXLEN && len <= avail && start[len - a] == end[len])
	{
		if (start + len == end)
			a = len;
	}
	return (len);
}

static int	ft_deflate_encode_lendst(t_ztreamp strm, size_t len, size_t dst)
{
	// TODO handle len == 258
	int		extra;
	int		tmp;

	extra = len < 11 ? 0 : (1 << ft_fls(len - 3) - 2);
	extra = len == 258 ? 0 : extra; // TODO: prettify
	tmp =  len < 11 ? len + 254 : 265 + extra * 4 + (len - 11) / (1 << extra);
	put_bits(strm, len == 285 ? 258 : tmp, 7);
	extra = dst < 5 ? 0 : 1 << (ft_fls(dst - 1) - 2);
	// TODO: Handle max encoding dst (in match)
	tmp = dst < 5 ? dst - 1 : 2 + extra * 2 + (dst - 1 - (1 << (extra + 2))
			/ (1 << (extra + 2))); // TODO: Think this is right. Check in morning
	
}

static int	ft_deflate_encode_match(t_ztreamp strm, t_list *hashp, int flush)
{
	t_list	*longest;
	size_t	len_longest;
	size_t	len;

	// TODO Handle flush
	len_longest = 0;
	while (hashp != 0) // && flush != NO_FLUSH ?? ////
	{
		len = ft_deflate_match_str((t_byte *)hashp->content,
				strm->next_in, strm->available_in);
		if (len > len_longest && len > 3)
			longest = hashp;
		if (len == FT_ZMAXLEN || len == strm->available_in)
			break ;
	}
	if (longest == 0)
		return (-1);
	
	return ((int)len);
}

static int	ft_deflate_static(t_zstreamp strm, int flush)
{
	t_list		hashlist[FT_ZHASHSIZE];
	int			hash;

	hash = 0;
	while (hash < FT_ZHASHSIZE)
		hashlist[hash++] = 0;
	while (strm->available_in > 3)
	{
		hash = strm->next_in[0] + strm->next_in[1] + strm->next_in[2];
		if (hashlist[hash] != 0)
			if (ft_deflate_encode_match(strm, hashlist[hash], int flush) != -1)
				continue ;
		// TODO: check error in stream here
	}
}

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
