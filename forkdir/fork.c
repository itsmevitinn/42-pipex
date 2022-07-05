#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
	int x = 1;
	fork();
	fork();
	fork();
	fork();
	// child process because return value zero
	if (fork() == 0)
        printf("child %d\n", ++x);
    // parent process because return value non-zero.
    else
        printf("parent %d\n", --x);
}
int main()
{
    forkexample();
    return 0;
}
