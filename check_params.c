/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:25:35 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 00:42:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	check_params(int arg)
{
	if (arg != 5)
	{
		errno = 121;
		perror("Invalid parameters!");
		exit(1);
	}
}
