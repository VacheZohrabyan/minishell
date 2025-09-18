/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:54:18 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/18 16:22:43 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	cmd_echo(t_command *command)
{
	int		i;
	int		newline;
	char	*str;

	i = 1;
	newline = 0;
	str = ft_strdup("");
	if (ft_strcmp(command->argv[i], "$?") == 0)
	{
		write (STDOUT_FILENO, ft_itoa(g_exit_status), ft_strlen(ft_itoa(g_exit_status)));
		write (STDOUT_FILENO, "\n", 1);
		return 0;
	}
	while (command->argv[i] && !ft_strcmp(command->argv[i], "-n"))
	{
		newline = 1;
		i++;
	}
	while (command->argv[i])
	{
		str = ft_strjoin_gnl(str, command->argv[i]);
		if (command->argv[i + 1])
			str = ft_strjoin_gnl(str, " ");
		i++;
	}
	if (newline)
		ft_putstr_fd(str, 2);
	else
		ft_putendl_fd(str, 2);
	free(str);
	return (0);
}
