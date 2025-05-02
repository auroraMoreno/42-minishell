/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 10:56:31 by aumoreno          #+#    #+#             */
/*   Updated: 2022/09/25 10:56:31 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s_dup;

	s_dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!s_dup)
		return (0);
	ft_memcpy (s_dup, s1, ft_strlen(s1) + 1);
	return (s_dup);
}
