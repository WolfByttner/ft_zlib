/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 09:46:35 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/22 20:45:14 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include <inttypes.h>
#include "ft_zlib_detail.h"
#ifndef ULONG_BIT
# define ULONG_BIT CHAR_BIT * sizeof(t_ulong)
# define REVERSE(b) (b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU) * 0x10101LU >> 16)
#endif

/*
** http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits
*/

static inline t_uchar	reverse_bits(int32_t b)
{
	return((t_uchar)(((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU))
			* 0x10101LU >> 16));
}

static inline int	strm_fill_bitbuff(t_zstream *strm)
{
	t_uint		i;
	t_uint		end;

	i = 0;
	strm->bitbuff = 0L;
	strm->bitcnt = 0;
	if (strm->available_in == 0)
	{
		strm->errno = FT_ZENO_INPUT;
		return (-1);
	}
	end = sizeof(t_ulong) < strm->available_in ? sizeof(t_ulong)
			: strm->available_in;
	i = 0;
	while (i++ < end)
	{
		strm->bitbuff <<= CHAR_BIT;
		strm->bitbuff += reverse_bits(strm->next_in[i - 1]);
		strm->bitcnt += CHAR_BIT;
		strm->available_in--;
	}
	strm->next_in += i - 1;
	printf("Buff is %lu|%lu|%p\n", strm->bitbuff,i , strm->next_in);
	printf("ulong %lu\n", sizeof(t_ulong));
	return (0);
}

/*
** Allows [number of bits in long] - 1 bits
**
** This function gets [num] bits from the input stream
** and returns them with the last read bit as the least significant bit.
** All bits higher than [num] are zeroed.
**
** For example, if the input stream reads .. 0101.... ....1000 ..
** the function will return '10100001' which is 'q' + 48 ['00110000' in the
** static huffman]. The function reads bits right-to-left
** and bytes left-to-right.
*/

t_ulong				get_bits(t_uint num, t_zstream *strm)
{
	t_ulong		storage;
	t_uint		tmp;

	storage = 0L;
	tmp = 0;
	if (num >= ULONG_BIT || num == 0)
		strm->errno = FT_ZEBITS_REQ;
	else
	{
		if (num > strm->bitcnt)
		{
			printf("\n purging %u, is %lu\n", strm->bitcnt, strm->bitbuff);
			storage = ((1L << strm->bitcnt) - 1) & (strm->bitbuff
					>> (ULONG_BIT - strm->bitcnt)); 
			num -= strm->bitcnt;
			storage <<= num;//(num - (tmp = strm->bitcnt));
			tmp = strm->bitcnt;
			printf("To keep %lu\n", storage);
			if (strm_fill_bitbuff(strm) == -1 || num == 0)
				return (storage);
		}
		printf("%lu buff is \n", strm->bitbuff);
		storage += ((1L << num) - 1) & (strm->bitbuff >> (ULONG_BIT - num));
		strm->bitbuff <<= num;
		strm->bitcnt -= num;
	}
	return (storage);
}
