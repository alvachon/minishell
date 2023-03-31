/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:23:42 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:21:10 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"
#include "../includes/minishell.h"

int	z_pwd(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	(void)env;
	while (env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
		i++;
	temp = ft_substr(g_data.env[i], 4, ft_strlen(env[i]));
	printf("%s\n", temp);
	free (temp);
	return (errno);
}
