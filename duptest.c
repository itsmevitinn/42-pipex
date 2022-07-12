#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int fdoutfile = open("outfile.txt", O_WRONLY);
	
	dup2(fdoutfile, 1);
	char *writefile;
	writefile = malloc(15);
	read(0, writefile, 15);
	write(1, writefile, 15);
}
