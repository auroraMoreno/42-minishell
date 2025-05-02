/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 10:40:19 by aumoreno          #+#    #+#             */
/*   Updated: 2022/09/25 10:40:19 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*tmp;
	char	*d;

	tmp = (char *)src;
	d = (char *)dst;
	if (tmp < d)
	{
		while (n--)
			d[n] = tmp[n];
	}
	else
		ft_memcpy(d, tmp, n);
	return (dst);
}
