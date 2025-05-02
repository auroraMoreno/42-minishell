/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:42:00 by aumoreno          #+#    #+#             */
/*   Updated: 2023/04/05 10:42:00 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	size_t			len;
	unsigned int	i;

	if (s == NULL || f == NULL)
	{
		return (NULL);
	}
	len = ft_strlen(s);
	r = (char *)malloc(len + 1);
	if (r == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		r[i] = f(i, s[i]);
		i++;
	}
	r[len] = '\0';
	return (r);
}
