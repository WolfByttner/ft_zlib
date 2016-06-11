/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inflate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 12:59:23 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 13:06:42 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"

int		ft_inflate(t_zstreamp strm, int level)
{
	(void)get_bits(19, strm); // for testing
	return (0);
}
