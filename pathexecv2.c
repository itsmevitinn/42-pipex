#include "pipex.h"
#include <stdio.h>

void	pathexecv2(char *argv[])
{
	extern char **environ;
	char **paths;
	char **arguments;
	int i;
	int j;
	j = 0;
	i = 0;
	arguments = ft_split(argv[3], ' ');
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], "/");
		paths[j] = ft_strjoin(paths[j], arguments[0]);
		if (!access(paths[j], F_OK | X_OK))
			execve(paths[j], arguments, NULL);
		j++;
	}
}
