/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:46:23 by aumoreno          #+#    #+#             */
/*   Updated: 2023/06/24 13:00:53 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(long nb)
{
	int	lgth;

	lgth = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		lgth++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		lgth++;
	}
	return (lgth);
}

char	*ft_logic_itoa(long nb, int l, char *str)
{
	while (nb > 0)
	{
		str[l] = (nb % 10) + '0';
		nb = nb / 10;
		l--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		l;

	nb = n;
	l = len(nb);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	str[l--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	str = ft_logic_itoa(nb, l, str);
	return (str);
}
