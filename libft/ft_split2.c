/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:35:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/19 16:24:16 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_splits(char *s, char c);
static int	sub_len(char *s, char c);
static void	ft_free(char **final, int offset);

char	**ft_split2(char const *s, char c)
{
	char	**final;
	int		splits;
	int		offset;
	int		substring;

	offset = 0;
	splits = count_splits((char *)s, c);
	final = malloc(sizeof(char *) * (splits + 1));
	if (final == NULL)
		return (NULL);
	final[splits] = NULL;
	while (offset < splits)
	{
		while (*(char *)s != '\0' && *(char *)s == c)
			s++;
		substring = sub_len((char *)s, c);
		final[offset] = ft_substr(s, 0, substring);
		if (!final[offset++])
		{
			ft_free(final, offset);
			return (NULL);
		}
		s += substring;
	}
	return (final);
}

static void	ft_free(char **final, int offset)
{
	while (offset-- > 0)
		free(final[offset]);
	free(final);
}

static int	count_splits(char *str, char c)
{
	int	sublen;
	int	splitnum;

	splitnum = 0;
	while (*str != '\0')
	{
		while (*str && *str == c)
			str++;
		sublen = sub_len(str, c);
		str += sublen;
		if (sublen)
			splitnum++;
	}
	return (splitnum);
}
#include <stdio.h>
static int	sub_len(char *str, char c)
{
	int	len;

	len = 0;
	if (*str++ == 39)
	{
		// printf("Entrei no if\n");
		// return(13);
		while (*str != 39)
		{
			// write(1, "entrei while\n", 13);
			str++;
			len++;
		}
		str++;
		len++;
	}
	while (*str != '\0' && *str != c)
	{
		str++;
		len++;
	}
	return (len);
}
