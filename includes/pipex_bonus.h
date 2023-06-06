/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:53:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/06 11:23:49 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>

# define HEREDOC 0

void	exit_handler(void);
int		open_file(char *file, int n, char **av, char **envp);
char	*get_path(char *cmd, char **env, int i);
char	*ft_free_tab(char **tab);

#endif