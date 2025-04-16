#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* Mandatory functions */
void	error(char *msg);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);

/* Bonus functions */
int		open_file(char *argv, int i);
void	usage(void);

#endif