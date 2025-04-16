#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd, int filein)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execute(argv[2], envp);
}

void	child2_process(char **argv, char **envp, int *fd, int fileout)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	execute(argv[3], envp);
}

void	pipex(char **argv, char **envp, int filein, int fileout)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		error("\033[31mError: Pipe Creation\n\e[0m");
	pid1 = fork();
	if (pid1 == -1)
		error("\033[31mError: Pipe Creation\n\e[0m");
	if (pid1 == 0)
		child_process(argv, envp, fd, filein);
	pid2 = fork();
	if (pid2 == -1)
		error("\033[31mError: Pipe Creation\n\e[0m");
	if (pid2 == 0)
		child2_process(argv, envp, fd, fileout);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fileout;
	int	filein;

	if (argc == 5)
	{
		filein = open(argv[1], O_RDONLY, 0777);
		fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (filein == -1)
			error("\033[31mError: Permission denied\n\e[0m");
		if (fileout == -1)
			error("\033[31mError: Permission denied\n\e[0m");
		pipex(argv, envp, filein, fileout);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
