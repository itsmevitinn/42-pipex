/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:02:07 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 01:04:49 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_listgnl	*stash)
{
	int			i;
	t_listgnl	*current;

	current = ft_lstlast_gnl(stash);
	i = 0;
	if (stash == NULL)
		return (0);
	while (current->string[i])
	{
		if (current->string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_listgnl	*ft_lstlast_gnl(t_listgnl *stash)
{
	t_listgnl	*current;

	current = stash;
	while (current)
	{
		if (!current->next)
			return (current);
		current = current->next;
	}
	return (current);
}

void	generate_line(t_listgnl	*stash, char	**list)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->string[i])
		{
			if (stash->string[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*list = malloc(sizeof(char) * (len + 1));
	if (*list == NULL)
		return ;
}

void	free_stash(t_listgnl *stash)
{
	t_listgnl	*temp;
	t_listgnl	*current;

	current = stash;
	while (current)
	{
		free(current->string);
		temp = current->next;
		free(current);
		current = temp;
	}
}

int	ft_strlen_gnl(const char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
