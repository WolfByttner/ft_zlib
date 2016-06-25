/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 12:59:23 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/25 19:54:08 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"
#include <math.h>

/*
** Naming scheme [algorithm]_["byte" type]_[huffman type]
*/

/*
** This function decompresses a length-distance pair
** according to the fixed huffman tree described in
** Section 3.2.6 in RFC 1951 from the IETF
** http://tools.ietf.org/html/rfc1951#section-3.2.6
** -
** The encoding specifies values between 256 and 285, encoded
** as 0b0000000 to 0b0011101 (plus 2 trailing bytes) in the stream.
** For clarity, 29 is written as 285 - 256.
*/


static int	inflate_pair_static(t_zstreamp strm, t_ulong len)
{
	int			extra;
	int			dst;
	const int	tabl[] = { 3, 11, 19, 35, 67, 131 };
	const int	tabd[] = { 1, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385 };

	extra = (len == 285 - 256 ? 0 : (len > 8) * ((len - 5) / 4));
	printf("%lu}%lu len extra\n", len, extra);
	if (len != 285 - 256)
		len = tabl[extra] + (extra ? get_bits(extra, strm) : 0)
			+ (len % 4) * extra + (len < 9 ? len - 1 : 0);
			//(len > 264) * ((len - 261) / 4) * (len - tabl[extra]);
	else
		len = 258;
	dst = get_bits(5, strm);
	extra = (dst > 3) * ((dst - 2) / 2);
	dst = tabd[extra] + (extra ? get_bits(extra, strm) : 0)
			+ (dst % 2) * (1 << extra) + (!extra) * (dst / 2) * 2;
	printf("Length %lu - distance %lu\n", len, dst);
	extra = 0;
	while (extra < len && extra < strm->available_out)
	{
		strm->next_out[extra] = strm->next_out[-dst + (extra % dst)];
		extra++;
	}
	if (extra < len)
		; // TODO error here
	strm->next_out += len;
	strm->available_out -= len;
	strm->total_read_out += len;
	return (0);
	// TODO: Add lz77 retrieval based on len and dst
} 

/*
** This function takes an 8-bit or 9-bit [TODO] byte and puts
** its literal value on the output stream.
** nbits is the number of bits, 8 or 9. bits needs to be adjusted to start
** from '0b00110000' (nbits == 8) or '0b110010000' (nbits == 9)
*/

static int	inflate_literal_static(t_zstreamp strm, t_ulong bits, int nbits)
{
	(*(strm->next_out++)) = (t_uchar)(bits - (nbits == 8 ? 48 : 400));
	printf("%c <-- is", *(strm->next_out - 1));
	strm->available_out--;
	strm->total_read_out++;
}

/*
** Static huffman table
** The first if is for literals
*/

static int	ft_inflate_static(t_zstreamp strm, int level)
{
	t_ulong		bits;

	//TODO need to have buffered encoding here

	while (1 /* always true // strm->available_in > 0 */)
	{
		printf("Looping\n");
		bits = get_bits(7, strm);
		if (24 <= bits && bits <= 95)
			inflate_literal_static(strm, (bits << 1) + get_bits(1,strm), 8);
		else if (1 <= bits && bits <= 23)
			inflate_pair_static(strm, bits);
		else if (100 <= bits && bits <= 127)
			inflate_literal_static(strm, (bits << 2) + get_bits(2, strm), 9);
		else if (0 == bits)
		{
			printf("Exiting %lu\n", bits);
			return (0);
		}
		else
			inflate_pair_static(strm, (bits << 1) + get_bits(1, strm));
	printf(" <- %u literal\n", bits);
		// TODO check for errors in strm here
	}
	printf ("Suspect exit\n");
}

int		ft_inflate(t_zstreamp strm, int level)
{
	printf("Start bb%lu\n", get_bits(19, strm)); // TODO for testing, throw away these
	ft_inflate_static(strm, level);
	return (0);
}
