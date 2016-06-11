/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 09:46:35 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 12:50:23 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include "ft_zlib_detail.h"
#ifndef ULONG_BIT
# define ULONG_BIT CHAR_BIT * sizeof(t_ulong)
#endif

static inline int	strm_fill_bitbuff(t_zstream *strm)
{
	t_uint		i;

	i = 0;
	strm->bitbuff = 0L;
	strm->bitcnt = 0;
	if (strm->available_in == 0)
	{
		strm->errno = FT_ZENO_INPUT;
		return (-1);
	}
	i = sizeof(t_ulong) < strm->available_in ? sizeof(t_ulong)
			: strm->available_in;
	while (i-- > 0)
	{
		strm->bitbuff <<= CHAR_BIT;
		printf("%lu new buff\n", strm->bitbuff);
		strm->bitbuff += *strm->next_in++;//; << CHAR_BIT * i);
		strm->bitcnt += CHAR_BIT;
		strm->available_in--;
	}
	printf("Strm is %ld\n", strm->bitbuff);
	return (0);
}

t_ulong				get_bits(t_uint num, t_zstream *strm)
{
	t_ulong		storage;

	storage = 0L;
	if (num > ULONG_BIT || num == 0)
		strm->errno = FT_ZEBITS_REQ;
	else
	{
		if (num >= strm->bitcnt)
		{
			storage = strm->bitbuff;
			storage <<= (num -= strm->bitcnt);
			if (strm_fill_bitbuff(strm) == -1)
				return (storage);
		}
		storage += strm->bitbuff >> ULONG_BIT - num;
		strm->bitbuff <<= num;
		strm->bitcnt -= num;
	}
	return (storage);
}
