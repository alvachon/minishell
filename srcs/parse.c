/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 13:55:10 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_print(int i, t_cmd *data)
{
	if (data->input[0] != '<' || data->input[0] != '>'
		|| data->input[0] != '|')
	{
		if (data->input[0] == 34)
			trim_guil(data, 34, 1);
		else if (data->input[0] == 39)
			trim_guil(data, 39, 1);
		else
			trim_guil(data, 0, 0);
	}
	i = ft_strlen(data->print);
	while (i)
	{
		data->input++;
		i--;
	}
}

char	*ft_strpaste(char *already_here, char *new)
{
	unsigned int	i;
	unsigned int	j;
	char			*fusion;

	i = 0;
	j = 0;

	if (!new)
		return (NULL);
	if (!already_here)
		return (new);
	fusion = ft_calloc((ft_strlen(already_here) + ft_strlen(new)) + 1, sizeof(char));
	if (!fusion)
		return (NULL);
	if (ft_strlen(already_here) == 1 && already_here[0] == '/' && new[0] == '/')
		new++;
	while (already_here[i] != '\0')
	{
		fusion[i] = already_here[i];
		i++;
	}
	while (new[j] != '\0')
	{
		fusion[i + j] = new[j];
		j++;
	}
	fusion[i + j] = '\0';
	if (already_here)
		free(already_here);
	return (fusion);
}

void	add_section(t_cmd *data)
{
	int		i;
	char	*temp;
	char	*buff;
	int		index;

	i = 0;
	buff = ft_substr(data->input, 0, 1);
	data->input++;
	i = chartrim(data->input, '/');
	temp = ft_substr(data->input, 0, i);
	printf ("%s\n", temp);
	//if (ft_strncmp(temp, "..", 2) == 0 && ft_strncmp(data->input, "..", 2) == 0)
		//option(data, "DIRECT", 1, 2);
	if (ft_strncmp(data->input, "..", 2) != 0)
	{
		buff = ft_strpaste(buff, temp);
		data->path = ft_strpaste(data->path, buff);
		free(temp);
	}
	else
	{
		index = 0;
		while (data->path[ft_strlen(data->path) - index] != '/')
			index++;
		index = ft_strlen(data->path) - index;
		if (index == 0)
			index = 1;
		free (temp);
		temp = ft_substr(data->path, 0, index);
		free(data->path);
		data->path = ft_strdup(temp);
		free (temp);
	}
	while (i--)
		data->input++;
	if (buff != NULL)
		free(buff);
}

void	keep_option(t_cmd *data)
{
	int i;

	i = 0;
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
		option(data, "-n", 1, 2);
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "../", 3) == 0)
	{
		data->input += 2;
	}*/
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "..", 2) == 0)
	{
		option(data, "BACK", 1, 2);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, ".", 1) == 0)
	{
		option(data, "STAY", 1, 1);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "~/", 2) == 0)
	{
		//option(data, "FIND", 1, 0);
		printf("%s\n", data->path);
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
	{
		while (data->input[0] == '/')
			add_section(data);
	}
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "./", 2) == 0)
	{
		option(data, "STAY", 1, 1);
		keep_option(data);
	}*/
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
		option(data, "DIRECT", 0, 0);*/
	/*else if (strcmp(data->built, "cd") == 0)
		option(data, "HOME", 0, 0);//bug here*/
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str);//echo seulement
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free (str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input); //echo hello < world -> must not work.
}

t_cmd	parse(t_cmd data)
{
	int	i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);
		keep_option(&data);
		keep_print(i, &data);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}
