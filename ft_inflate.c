/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 12:59:23 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 15:09:30 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"

static int	decode_literal_static(t_zstreamp strm, t_ulong bits)
{
	((t_byte)(*(strm->next_out))) = (t_uchar)bits;
	strm->available_out--;
}

/*
** Static huffman table
** The first if is for literals
*/

static int	ft_inflate_static(t_zstreamp strm, int level)
{
	t_ulong		bits;

	//need to have buffered encoding here
	while (strm->available_in > 0)
	{
		bits = get_bits(7, strm);

		if (24 <= bits && bits <= 95)
			decode_literal_static(strm, (bits << 7) + get_bits(1,strm));
	}
}

int		ft_inflate(t_zstreamp strm, int level)
{
	(void)get_bits(19, strm); // for testing, throw away these

	return (0);
}
