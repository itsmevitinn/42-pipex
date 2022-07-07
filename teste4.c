#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fdinfile = open("infile.txt", O_RDONLY, 0777);
	dup2(fdinfile, 0);
	char *buffer;
	buffer = malloc(4);
	read(1, buffer, 4);
	printf("%s", buffer);
}
