/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:15:06 by aumoreno          #+#    #+#             */
/*   Updated: 2022/09/25 11:15:06 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	mem;

	if (*little == '\0')
		return ((char *)big);
	mem = ft_strlen((char *)little);
	while (*big != '\0' && len-- >= mem)
	{
		if (*big == *little && ft_memcmp(big, little, mem) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
