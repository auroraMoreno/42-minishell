/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:19:13 by aumoreno          #+#    #+#             */
/*   Updated: 2023/06/24 14:11:44 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		substr = ft_calloc(1, 1);
		return (substr);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	substr = ft_calloc((len + 1), 1);
	if (!substr)
		return (0);
	if (ft_strlen(s) > (size_t)start)
	{
		ft_strlcpy(substr, (char *)(s + start), len + 1);
	}
	return (substr);
}
