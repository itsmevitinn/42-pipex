/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 04:24:43 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/26 13:41:13 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(char **argv, int **readwrite)
{
	char	*line;
	char	*check;
	int		fdtemp;
	int		fdinfile;

	fdtemp = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdtemp == -1)
		error_msg("tempfile.txt", 1);
	write(1, "heredoc> ", 9);
	line = get_next_line(STDIN_FILENO);
	check = ft_strtrim(line, "\n");
	while (ft_strncmp(check, argv[2], ft_strlen(check)) != 0 && line != NULL)
	{
		free(check);
		write(fdtemp, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		check = ft_strtrim(line, "\n");
	}
	close(fdtemp);
	fdinfile = open("tempfile.txt", O_RDONLY);
	unlink("tempfile.txt");
	runcmds(argv[3], fdinfile, readwrite[0][1]);
}

int	do_files(char *argv, int type)
{
	int	fdfile;

	if (type == 0)
	{
		fdfile = open(argv, O_RDONLY);
		if (fdfile == -1)
			error_msg(argv, 1);
	}
	else if (type == 1)
	{
		fdfile = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdfile == -1)
			error_msg(argv, 1);
	}
	else
	{
		fdfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fdfile == -1)
			error_msg(argv, 1);
	}
	return (fdfile);
}
