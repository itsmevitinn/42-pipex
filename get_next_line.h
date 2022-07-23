/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:58 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/23 10:42:01 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*string;
	struct s_list	*next;
}					u_list;

char	*get_next_line(int fd);
void	read_and_stash(u_list **stash, int fd);
void	add_to_stash(u_list **stash, char *buffer, int readed);
void	extract_line(u_list *stash, char **line);
void	clean_stash(u_list **stash);
int		found_newline(u_list *stash);
u_list	*ft_lstlast_gnl(u_list *stash);
void	generate_line(u_list *stash, char	**list);
void	free_stash(u_list *stash);
int		ft_strlen_gnl(const char *str);
#endif
