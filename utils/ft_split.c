/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:17:37 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/28 15:06:09 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	skip_next_is_c(char const *s, char c, int i, int b)
{
	if (b == 0)
	{
		while (s[i] && s[i] == c)
			i++;
	}
	else if (b == 1)
	{
		while (s[i] && s[i] != c)
			i++;
	}
	else if (b == 2)
	{
		if (s[i] == c)
			return (1);
		return (0);
	}
	return (i);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	previous;

	i = 0;
	previous = 1;
	count = 0;
	while (s[i])
	{
		if (skip_next_is_c(s, c, i, 2))
			previous = 1;
		else
		{
			if (previous == 1)
				count++;
			previous = 0;
		}
		i++;
	}
	return (count);
}

static char	**ft_free1(char **res, int a)
{
	while (a >= 0)
	{
		free(res[a]);
		a--;
	}
	free(res);
	return (NULL);
}

static char	**ft_split2(char const *s, char c, char **res)
{
	int		i;
	int		j;
	int		a;
	int		k;

	i = 0;
	a = 0;
	while (a < word_count(s, c))
	{
		i = skip_next_is_c(s, c, i, 0);
		j = skip_next_is_c(s, c, i, 1);
		k = 0;
		res[a] = malloc(sizeof(char) * (j - i + 1));
		if (!res[a])
			return (ft_free1(res, a));
		while (i < j)
			res[a][k++] = s[i++];
		res[a++][k] = '\0';
	}
	res[a] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (0);
	return (ft_split2(s, c, res));
}
