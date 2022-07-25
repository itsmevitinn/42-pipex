/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 12:59:24 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 00:08:53 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_listgnl
{
	char			*string;
	struct s_listgnl	*next;
}					t_listgnl;

char	*get_next_line(int fd);
void	read_and_stash(t_listgnl **stash, int fd);
void	add_to_stash(t_listgnl **stash, char *buffer, int readed);
void	extract_line(t_listgnl *stash, char **line);
void	clean_stash(t_listgnl **stash);
int		found_newline(t_listgnl *stash);
t_listgnl	*ft_lstlast_gnl(t_listgnl *stash);
void	generate_line(t_listgnl *stash, char	**list);
void	free_stash(t_listgnl *stash);
int		ft_strlen_gnl(const char *str);
#endif
