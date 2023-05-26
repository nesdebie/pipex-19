/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:53:59 by nesdebie          #+#    #+#             */
/*   Updated: 2023/05/26 11:22:26 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_SUCCESS);
	}
}

static void	heredoc_input(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(HEREDOC);
		if (!ret)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(ret, av[2], ft_strlen(av[2])))
		{
			free(ret);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

static void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		heredoc_input(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(0);
	}
}

static void	ft_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (ac < 5)
		exit_handler();
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			exit_handler();
		i = 3;
		fd_out = open_file(av[ac - 1], 1);
		here_doc(av);
	}
	else
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < ac - 2)
		ft_pipe(av[i++], env);
	dup2(fd_out, 1);
	exec(av[ac - 2], env);
}
