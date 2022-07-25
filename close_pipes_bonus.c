/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 00:16:30 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 01:04:12 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_first_pipe(int argc, int **readwrite)
{
	int	indexchecker;

	indexchecker = 0;
	while (indexchecker < argc - 4)
	{
		if (indexchecker == 0)
			close(readwrite[indexchecker][0]);
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	close_middle_pipes(int argc, int usedpipe, int **readwrite)
{
	int	indexchecker;

	indexchecker = 0;
	while (indexchecker < argc - 4)
	{
		if (indexchecker == usedpipe - 1)
			close(readwrite[indexchecker][1]);
		else if (indexchecker == usedpipe)
			close(readwrite[indexchecker][0]);
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	close_last_pipe(int argc, int usedpipe, int **readwrite)
{
	int	indexchecker;

	indexchecker = 0;
	while (indexchecker < argc - 4)
	{
		if (indexchecker == usedpipe - 1)
			close(readwrite[indexchecker][1]);
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	close_all(int argc, int **readwrite)
{
	int	index;

	index = 0;
	while (index < argc - 4)
	{
		close(readwrite[index][0]);
		close(readwrite[index][1]);
		index++;
	}
}
