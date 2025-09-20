/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:54:18 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/20 13:18:09 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

static char	*print_echo(t_command *command, int start)
{
	int		i;
	char	*str;
	char	*tmp;

	i = start;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (command->argv[i])
	{
		if (ft_strcmp(command->argv[i], "$?") == 0)
			tmp = ft_itoa(g_exit_status);
		else
			tmp = ft_strdup(command->argv[i]);
		if (!tmp)
			return (free(str), NULL);
		str = ft_strjoin_gnl(str, tmp);
		if (command->argv[i + 1])
			str = ft_strjoin_gnl(str, " ");
		i++;
	}
	return (str);
}

static int	check_for_newline(t_command *command, int *start)
{
	int	newline;
	int	j;
	int	i;

	i = 1;
	newline = 1;
	while (command->argv[i] && command->argv[i][0] == '-'
		&& command->argv[i][1] == 'n')
	{
		j = 2;
		while (command->argv[i][j] == 'n')
			j++;
		if (command->argv[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	*start = i;
	return (newline);
}

int	cmd_echo(t_command *command)
{
	int		start;
	int		newline;
	char	*str;

	start = 1;
	newline = check_for_newline(command, &start);
	str = print_echo(command, start);
	if (!str)
		return (1);
	if (newline)
		ft_putendl_fd(str, STDOUT_FILENO);
	else
		ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
	return (0);
}
