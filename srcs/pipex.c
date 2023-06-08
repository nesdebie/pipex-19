/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:50:03 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/08 10:36:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(EXIT_FAILURE);
	path = get_path(s_cmd[0], env, 0);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		ft_free_tab(s_cmd);
		exit(126);
	}
}

static void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	if (fd == -1)
	{
		ft_putstr_fd(av[2], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(0);
	}
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

static void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
	if (fd == -1)
	{
		ft_putstr_fd(av[3], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(av[4], 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(1);
	}
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

static int	no_path(char **av, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (EXIT_SUCCESS);
		i++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(av[2], 2);
	ft_putendl_fd(" : No such file or directory", 2);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(av[3], 2);
	ft_putendl_fd(" : No such file or directory", 2);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int		p_fd[2];
	pid_t	pid;

	if (no_path(av, envp))
		exit(127);
	if (ac != 5)
	{
		ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_SUCCESS);
	}
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(av, p_fd, envp);
	parent(av, p_fd, envp);
}
