#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "pipex.h"
int check_params(int arg)
{
	if (arg != 5)
	{
		perror("Invalid parameters!\n");
		exit(1);
	}
	return (0);
}
