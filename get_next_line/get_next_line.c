/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:01:02 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 10:05:45 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_listgnl	*stash;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash(&stash, fd);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(t_listgnl **stash, int fd)
{
	char	*buffer;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		readed = read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buffer);
			return ;
		}
		buffer[readed] = '\0';
		add_to_stash(stash, buffer, readed);
		free(buffer);
	}
}

void	add_to_stash(t_listgnl **stash, char *buffer, int readed)
{
	int			i;
	t_listgnl	*end_stash;
	t_listgnl	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_listgnl));
	if (new_node == NULL)
		return ;
	new_node->string = malloc(sizeof(t_listgnl) * (readed + 1));
	if (new_node->string == NULL)
		return ;
	new_node->next = NULL;
	while (buffer[i] && i < readed)
	{
		new_node->string[i] = buffer[i];
		i++;
	}
	new_node->string[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	end_stash = ft_lstlast_gnl(*stash);
	end_stash->next = new_node;
}

void	extract_line(t_listgnl *stash, char	**line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(stash, line);
	j = 0;
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->string[i])
		{
			if (stash->string[i] == '\n')
			{	
				(*line)[j++] = stash->string[i];
				break ;
			}
			(*line)[j++] = stash->string[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_listgnl **stash)
{
	t_listgnl	*new;
	t_listgnl	*last;
	int			i;
	int			j;

	j = 0;
	new = malloc(sizeof(t_listgnl));
	if (stash == NULL || new == NULL)
		return ;
	last = ft_lstlast_gnl(*stash);
	i = 0;
	while (last->string[i] && last->string[i] != '\n')
		i++;
	if (last->string && last->string[i] == '\n')
		i++;
	new->string = malloc(sizeof(char) * ((ft_len(last->string) - i) + 1));
	new->next = NULL;
	if (new->string == NULL)
		return ;
	while (last->string[i])
		new->string[j++] = last->string[i++];
	new->string[j] = '\0';
	free_stash(*stash);
	*stash = new;
}
