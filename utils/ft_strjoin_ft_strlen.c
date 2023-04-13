/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ft_strlen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:13:53 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/13 14:50:31 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*s3;
	int				i;
	unsigned int	j;
	unsigned int	s1len;
	unsigned int	s2len;

	if (!s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3 = malloc(sizeof(*s3) * (s1len + s2len + 1));
	if (!s3)
	{
		free(s1);
		exit(0);
	}
	i = -1;
	j = 0;
	while ((unsigned int)++i < s1len)
		s3[i] = s1[i];
	while (j < s2len)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
