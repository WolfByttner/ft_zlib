/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zlib_detail.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 09:35:26 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 13:04:15 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This is the "private" implementation. It is liable to change
** without notice and programs should not depend on it.
** Please use public headers in ft_zlib.h
*/

#ifndef FT_ZLIB_DETAIL_H
# define FT_ZLIB_DETAIL_H
# include "ft_zlib.h"

/*
** TESTING ** REMOVE BEFORE SUBMISSION **
*/
#include <stdio.h>
/*
**
*/

t_ulong	get_bits(t_uint num, t_zstream *strm);

/*
** End ft_zlib_detail.h
*/
#endif
