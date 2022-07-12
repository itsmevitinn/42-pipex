#include "pipex.h"

int errorhandling (int fdinfile, int fdoutfile)
{
	if (fdinfile == -1 | fdoutfile == -1)
	{
		perror("Failed to open files!\n");
		exit(1);
	}
	return (0);
}
