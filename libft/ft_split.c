/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:02:27 by aumoreno          #+#    #+#             */
/*   Updated: 2023/06/23 12:02:27 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			i++;
		else if (s[i] < 32 || s[i] > 126)
			return (0);
		else
		{
			words++;
			while (s[i] && s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (words);
}

int	ft_free(int j, char **result)
{
	while (j >= 0)
	{
		if (result[j] != NULL)
		{
			free(result[j]);
		}
		j--;
	}
	free(result);
	return (0);
}

int	ft_copy_word(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			len = 0;
			while (s[i] && s[i] != c)
			{
				len++;
				i++;
			}
			result[++j] = (char *)malloc(sizeof(*s) * (len + 1));
			if (!result[j])
				return (ft_free(j, result));
			result[j][len] = '\0';
		}
	}
	return (1);
}

void	ft_fill(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
		}
		else
		{
			len = 0;
			while (s[i] && s[i] != c)
			{
				result[j][len] = s[i];
				len++;
				i++;
			}
			result[j][len] = '\0';
			j++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (s == NULL)
		return (0);
	words = ft_count_words(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (0);
	ft_copy_word(s, c, result);
	ft_fill(s, c, result);
	result[words] = 0;
	return (result);
}
