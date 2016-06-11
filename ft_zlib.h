/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 19:02:50 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/11 13:05:02 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ZLIB_H
# define FT_ZLIB_H

/*
** Defined constants
*/

# define FT_ZENO_INPUT 8
# define FT_ZEBITS_REQ 2
# define FT_ZENOMEM 1

/*
** Stream architecture
*/

typedef unsigned char	t_byte;
typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;
typedef unsigned char	t_uchar;

typedef struct			s_zstream
{
	const t_byte		*next_in;
	t_uint				available_in;
	t_ulong				total_read_in;
	const t_byte		*next_out;
	t_uint				available_out;
	t_ulong				total_read_out;
	int					data_type;
	unsigned char		settings;
	int					errno;
	t_ulong				bitbuff;
	t_uint				bitcnt;
}					t_zstream;

typedef t_zstream		*t_zstreamp;

/*
** Core functions
*/

extern int				ft_deflate_init(t_zstreamp strm, int level);
extern int				ft_deflate(t_zstreamp strm, int flush);
extern int				ft_deflate_end(t_zstreamp strm, int level);
extern int				ft_inflate_init(t_zstreamp strm);
extern int				ft_inflate(t_zstreamp strm, int flush);
extern int				ft_inflate_end(t_zstreamp strm);

/*
** End core functions
*/

/*
** End FT_ZLIB_H
*/
#endif
