/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 12:59:23 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/12 01:08:57 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"

/*
** Naming scheme [algorithm]_["byte" type]_[huffman type]
*/

/*
** This function decompresses a length-distance pair
** according to the fixed huffman tree described in
** Section 3.2.6 in RFC 1951 from the IETF
** http://tools.ietf.org/html/rfc1951#section-3.2.6
*/

static int	inflate_pair_static(t_zstreamp strm, t_ulong bits)
{

}

/*
** This function takes an 8-bit or 9-bit [TODO] byte and puts
** its literal value on the output stream.
*/

static int	inflate_literal_static(t_zstreamp strm, t_ulong bits)
{
	(*(strm->next_out)) = (t_uchar)bits - 48;
	printf("Literal %c \n", (char)bits);
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
	while (strm->available_in > 0)
	{
		bits = get_bits(7, strm);
		printf("These are the bits %lu\n", bits);
		if (24 <= bits && bits <= 95)
			inflate_literal_static(strm, (bits << 1) + get_bits(1,strm));
		else if (0 <= bits && bits <= 23)
			inflate_pair_static(strm, bits);
	}
}

int		ft_inflate(t_zstreamp strm, int level)
{
	printf("Start bb%lu\n", get_bits(19, strm)); // TODO for testing, throw away these
	ft_inflate_static(strm, level);
	return (0);
}
