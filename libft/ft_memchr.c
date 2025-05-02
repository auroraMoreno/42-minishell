/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 10:40:31 by aumoreno          #+#    #+#             */
/*   Updated: 2022/09/25 10:40:31 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	j;
	unsigned char	*str;

	str = (unsigned char *)s;
	j = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == j)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
