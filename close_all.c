/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:05:14 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/21 00:22:44 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
