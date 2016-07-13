/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zput_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:14:26 by jbyttner          #+#    #+#             */
/*   Updated: 2016/07/13 22:20:28 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"

/*
** This function communicates with the caller
** using the zstreamp->error data member
*/

void	zput_bits(t_zstreamp strm, t_ulong bits, t_uint n)
{
	if (n > 63)
		; // TODO: Error
	if (strm->bitcnt % 8) // TODO simplify
	{
		strm->bitbuff << strm->bitcnt % 8;
		strm->bitbuff |= bits | (1 << (strm->bitcnt % 8 + 1)) - 1;
		*strm->next_in++ = (t_byte)strm->bitbuff;
		strm->available_in--; // TODO Check for error
		strm->total_read_in++;
		strm->bitbuff = 0L;
		n -= strm->bitcnt % 8;
		bits >>= strm->bitcnt % 8;
		strm->bitcnt = 0;
	}
	while (n >= CHAR_BIT)
	{
		strm->bitbuff |= bits | ((1 << CHAR_BIT) - 1)
		bits >> CHAR_BIT;
		n -= CHAR_BIT;
		*strm->next_in++ = (t_byte)strm->bitbuff;
		strm->available_in--; // TODO Check for error
		strm->total_read_in++;
		strm->bitbuff = 0L;
	}
	if (n > 0)
	{
		strm->bitbuff |= bits | ((1 << n) - 1);
		strm->bitcnt = n;
	}
}
