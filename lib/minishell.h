/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/02/02 12:06:17 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<errno.h>
# include<locale.h>
# include<signal.h>
# include"libft/libft.h"
# include<fcntl.h>

typedef struct s_argsandflags
{
	char	*buff;
	char	**arg;
	char	*path;
}			t_aflg;

int		ft_strcmp(char *s1, char *s2);
char	**ft_pathfinder(char *envp[]);
int		command_parse(char *cmd, char **env);
int		builtincheck(char **cmd);
int		envcheck(char **cmd);
int		functionparse_dispatch(char **env, char **cmd, int code);
void	error_msg(char *cmd);
void	echo_parse(char **cmd, char **env);
void	execute_echo(char *path, char **cmd, char **env);
void	free_echo(char *temp, char *temp2, char **env, int code);

#endif