#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

int		errorhandling(int fdinfile, int fdoutfile);
int		check_params(int arg);
void	pathexecv1(char *argv[]);
void	pathexecv2(char *argv[]);
#endif
