/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:56:23 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 22:45:55 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include <stdlib.h>

void	freeargs(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		free(arguments[i]);
		i++;
	}
	free (arguments);
}
