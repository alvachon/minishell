/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/29 16:08:41 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
*[0]BUILT
*[1]OPTION
*[2]REDIRECTION
![3]APPEND
4]INFILE
[5]PIPE
[6]REDIRECTION
[7]APPEND
[8]OUTFILE */

# include <stdio.h>
# include "history.h"
# include "libft/libft.h"
# include "readline.h"
# include <errno.h>
# include <fcntl.h>
# include <locale.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define FOREGROUND_JOB 1

typedef struct s_argsandflags
{
	char				*buff;
	char				**arg;
	char				*path;
}						t_aflg;

typedef struct s_terminal
{
	struct termios		mod_terminal;
	struct termios		new_options;
}						t_terminal;

enum					e_shell_state
{
	SH_READ,
	SH_EXEC,
};

typedef struct s_cmd
{
	char				*input;
	char				*built;
	char				*opt;//option
	char				*redir_input;//redirection, here doc
	char				*flag_delim;//append
	char				*infile;
	char				*pipe;
	char				*redir_output;
	char				*append;
	char				*outfile;
	char				*print;
	char				*path;
}						t_cmd;
typedef struct s_data
{
	char				**env;
	char				*built_path;
	char				*pwd;
	char				*oldpwd;
	enum e_shell_state	shell_state;
}						t_data;

t_data					g_data;

/*lexer.c*/
int						builtincheck(t_cmd *data, char **env);
int						lexer(char *input, char **env);

/*minishell.c*/
int						shell_process(char **env);

/*parse.c*/
void					keep_print(t_cmd *data);
void					keep_option(t_cmd *data);
void					keep_builtin(int i, t_cmd *data);
void					parse(t_cmd *data);
void					trim_guil(t_cmd *data, char c);

/*terminal_signal.c*/
void					handle_sig(int sign);
void					ctrl_c_eof(void);
void					init_shell(t_terminal *minishell, char **env);

/*utils_env.c*/
char					*set(char *var, int siz_var);
void					option(t_cmd *data, char *option, int trigger,
							int trim_size);

/*utils_global.c*/
void					set_global(char **env);
void					error_msg(char *cmd);
void					exit_msg(char *cmd);
void					sys_msg(char *reason, int code);
char					**ft_setenv(char **env);

/*utils_input.c*/
int						wordlen(char *input, int i);
char					*wordtrim(char *input, int i);
int						wordcount(char *str);
int						scan(char *input, char c);
int						chartrim(char *input, char c);

/*utils_trim.c*/
char					*ulstr(char *str);
char					*ltrim(char *input);
char					*rtrim(char *str);
char					*trimchar(char *file, char c);
int						sizebetweenchar(char *file, char c);
int						len_until_trigger(char *file, char c, int j);

/**/
int						ft_unsetcomp(const char *str, char *var);
int						ft_exportcomp(const char *str, char *var);

/*work_in_progress.c*/
void					keep_redir_input(t_cmd *data, int i);
char					*scan_end(t_cmd *data, int trig);
void					keep_flag_delim(t_cmd data, int i);

/*z_cd*/
int						delete_last(t_cmd *data);
void					rewrite(t_cmd *data, int i);
void					keep_user(t_cmd *data);
void					remake_path(t_cmd *data);
int						z_cd(t_cmd *data, char **env);
void					hard_path(t_cmd *data);

/*z_echo.c*/
void					z_echo(t_cmd *data);

/*z_env.c*/
int						z_env(char **env);

/*z_export*/
int						z_export(char *str);
char					**export_env(char *str);
char					*new_env_var(char *str, int pos);

/*z_pwd.c*/
int						z_pwd(char **env);

/*z_unset.c*/
int						z_unset(char *str);
char					**env_unset(char *str);

#endif
