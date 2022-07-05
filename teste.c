#include <stdio.h>
#include <unistd.h>
void forkexample()
{
	int x = 1;
	if (fork() == 0)
		printf("child %d\n", ++x);
	else
		printf("parent %d\n", --x);
}

int main()
{
	forkexample();
	return 0;
}
