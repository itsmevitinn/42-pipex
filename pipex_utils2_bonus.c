/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 04:24:43 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 10:12:56 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(char **argv, int **readwrite)
{
	char	*line;
	char	*check;
	int		fdheredoc;
	int		fdtemp;
	int		fdout;

	fdheredoc = open("here_doc", O_RDONLY);
	fdtemp = open("tempfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fdheredoc == -1 || fdtemp == -1)
		error_msg("Failed to open file!", 1);
	line = get_next_line(fdheredoc);
	check = ft_strtrim(line, "\n");
	while (ft_strncmp(check, argv[2], ft_strlen(check)) != 0 && line != NULL)
	{
		free(check);
		write(fdtemp, line, ft_strlen(line));
		free(line);
		line = get_next_line(fdheredoc);
		check = ft_strtrim(line, "\n");
	}
	close(fdtemp);
	fdout = open("tempfile.txt", O_RDONLY);
	unlink("tempfile.txt");
	runcmds(argv[3], fdout, readwrite[0][1]);
}

int	do_files(char *argv, int type)
{
	int	fdfile;

	if (type == 0)
	{
		fdfile = open(argv, O_RDONLY);
		if (fdfile == -1)
			error_msg("Failed to open infile!", 1);
	}
	else if (type == 1)
	{
		fdfile = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdfile == -1)
			error_msg("Failed to open outfile!", 1);
	}
	else
	{
		fdfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fdfile == -1)
			error_msg("Failed to open here_doc outfile!", 1);
	}
	return (fdfile);
}
