#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
	int id = fork();
	char *binaryPath = "/bin/bash";
	char *infile;
	char *cmd1;
	char *cmd2;
	char *outfile;
	infile = (char *)malloc(8 + ft_strlen(argv[1]));
	ft_strlcpy(infile, "infile=", 8);
	ft_strlcat(infile, argv[1], 8 + ft_strlen(argv[1]));
	
	cmd1 = (char *)malloc(6 + ft_strlen(argv[2]));
	ft_strlcpy(cmd1, "cmd1=", 6);
	ft_strlcat(cmd1, argv[2], 6 + ft_strlen(argv[2]));
	
	cmd2 = (char *)malloc(6 + ft_strlen(argv[3]));
	ft_strlcpy(cmd2, "cmd2=", 6);
	ft_strlcat(cmd2, argv[3], 6 + ft_strlen(argv[3]));
	
	outfile = (char *)malloc(9 + ft_strlen(argv[4]));
	ft_strlcpy(outfile, "outfile=", 9);
	ft_strlcat(outfile, argv[4], 9 + ft_strlen(argv[4]));
	
	char *const args[] = {binaryPath, "-c", "< $infile $cmd1 | $cmd2 > $outfile", NULL};
	char *const env[] = {infile, cmd1, cmd2, outfile, NULL};
	execve(binaryPath, args, env);
	return (0);
}
