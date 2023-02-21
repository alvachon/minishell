/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/09 15:07:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */
#include <ctype.h>//

#include "../includes/minishell.h"

int	envcheck(char **cmd)
{
	if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (7);
	else
		return (8);
}

int main(int ac, char **av, char **env)
{
	t_terminal		minishell;
	static char		*cmd;

	(void)av;
	if (ac != 2)
	{
		init_shell(&minishell, env);
		cmd = NULL;
  		while (FOREGROUND_JOB)
		{
			if (isatty(STDIN_FILENO))
			{
    			cmd = readline("\033[0m\033[34mminishell\033[0m\033[35m$ \033[0m");
				g_data.shell_state = SH_EXEC;
                if (!cmd)
                {
                    rl_on_new_line();
                    rl_redisplay();
                    write(1, "exit\n", 5);
                    exit(EXIT_SUCCESS);
                }
    			if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
            	{
					if (cmd)
      		    		free(cmd);
					continue;
    			}
				else if (command_parse(cmd, env) == 1)
                {
                    add_history(cmd);
					error_msg(cmd);
                }
				else
				{
					printf("Command done and freed, added to the history\n");
					add_history(cmd);
    				free(cmd);
				}
			}
			else
			{
				printf("\n(job process) Is redirected, not a terminal. \n");
			}
  		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}
