#include <errno.h>
#include "stdio.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(void)
{
	if (open("nonexistedfile.txt", O_RDONLY) == -1)
		printf("ERROR! %s", strerror(errno));
	if (open("nonexistedfile.txt", O_RDONLY) == -1)
		perror("pERROR!");
}
