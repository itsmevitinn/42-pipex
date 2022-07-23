/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/23 10:42:13 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(u_list	*stash)
{
	int		i;
	u_list	*current;

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

u_list	*ft_lstlast_gnl(u_list *stash)
{
	u_list	*current;

	current = stash;
	while (current)
	{
		if (!current->next)
			return (current);
		current = current->next;
	}
	return (current);
}

void	generate_line(u_list	*stash, char	**list)
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

void	free_stash(u_list *stash)
{
	u_list	*temp;
	u_list	*current;

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
