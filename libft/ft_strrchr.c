/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 10:39:14 by aumoreno          #+#    #+#             */
/*   Updated: 2023/06/24 14:21:01 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*innit;
	char		ctr;

	innit = s;
	ctr = c;
	while (*s)
		s++;
	while (*s != ctr)
	{
		if (s == innit)
			return (0);
		s--;
	}
	return ((char *) s);
}
