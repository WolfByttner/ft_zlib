/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 22:53:57 by jbyttner          #+#    #+#             */
/*   Updated: 2016/06/26 23:01:26 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_zlib_detail.h"
#include <fcntl.h>
#include <unistd.h>

double	drand(void)
{
	static double		seed = 21753632131.4

	return (seed = ((seed * 2683852617.7) % 1));
}

int		main(int ac, char **av)
{
	int			fds[2];
	t_zstream	strm;
	char		arr[10000];

	if (av < 3)
		return (-1);
	1 + (int)(drand * 62);
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fds[0] <= 0 || fds[1] <= 0)
		return (-1);
	strm.next_in = arr;
	strm.available_in = 10000;


}
